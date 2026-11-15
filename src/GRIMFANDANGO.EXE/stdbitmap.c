/* GRIMFANDANGO.EXE :: stdbitmap.c
 * functions 0x00473630 .. 0x0047b5f0 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00473630  stdLoadImage ---- */
/* Loads a .bm bitmap file; the frame surfaces hang off +0x78 Original name stdLoadImage (the
   remaster's GrimFandango (Linux): same body (stdLoadImageData, then stdBitmap_DeCompress); the
   std.c service between stdFPutc and stdLoadImageData in both builds; the earlier hand-made name
   stdBitmap_Load is the remaster's name of 0x47aa50); was stdBitmap_Load. */

stdBitmap * __cdecl stdLoadImage(char *filename,int param_2,int param_3)

{
  stdBitmap *psVar1;
  
  psVar1 = stdLoadImageData(filename,param_2,param_3);
  if (psVar1 != (stdBitmap *)0x0) {
    stdBitmap_DeCompress((int)psVar1);
  }
  return psVar1;
}

/* ---- 0x00473660  stdLoadImageData ---- */
/* Original name stdLoadImageData (the remaster's GrimFandango (Linux): strings: '.bm' | '.pic' |
   '.zbm' | '.gif'); was stdBitmap_LoadFile. */

stdBitmap * __cdecl stdLoadImageData(char *name,int a,int b)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint *puVar2;
  stdBitmap *psVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 *)(_frame + (0x20 - 0x4)))
  
  puVar2 = (uint *)strrchr(name,'.');
  if (puVar2 == (uint *)0x0) {
    uVar4 = 0xffffffff;
    pcVar7 = &DAT_004ddec4;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar7 = name;
    do {
      pcVar8 = pcVar7;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    puVar2 = (uint *)&DAT_004ddec4;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  strncpy(&local_8,puVar2,4);
  local_4 = 0;
  iVar5 = _stricmp((byte *)&local_8,&DAT_004ddec4);
  if (iVar5 == 0) {
    psVar3 = stdLbm_Load(name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004ddebc);
  if (iVar5 == 0) {
    psVar3 = (stdBitmap *)stdPcx_Load((uint)name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004ddeb4);
  if (iVar5 == 0) {
    psVar3 = stdGif_Load(name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004ddeb0);
  if ((iVar5 != 0) && (iVar5 = _stricmp((byte *)&local_8,&DAT_004ddea8), iVar5 != 0)) {
    iVar5 = _stricmp((byte *)&local_8,&DAT_004ddea0);
    if (iVar5 == 0) {
      psVar3 = (stdBitmap *)stdPic_Load((uint)name,a,b);
      return psVar3;
    }
    iVar5 = _stricmp((byte *)&local_8,&DAT_004dde98);
    if (iVar5 != 0) {
      return (stdBitmap *)0x0;
    }
    psVar3 = (stdBitmap *)stdBmp_Load((uint)name,a,b);
    return psVar3;
  }
  psVar3 = stdBitmap_Load(name,a,b);
  return psVar3;
}
#undef local_4
#undef local_8


/* ---- 0x00473810  stdWriteImage ---- */
/* Picks the writer from the file extension: .bm/.zbm (stdBitmap_Write, zbm marks format 5), .bmp,
   .gif, .pcx, .lbm Original name stdWriteImage (the remaster's GrimFandango (Linux): strings: 'lbm'
   | 'pcx' | 'zbm' | 'bmp'); was stdBitmap_SaveByExtension. */

int __cdecl stdWriteImage(char *filename,stdBitmap *bitmap)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 *)(_frame + (0x20 - 0x4)))
  
  puVar2 = (uint *)stdFnames_FindExt(filename);
  if (puVar2 == (uint *)0x0) {
    uVar4 = 0xffffffff;
    pcVar7 = &DAT_004ddec4;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar7 = filename;
    do {
      pcVar8 = pcVar7;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    puVar2 = (uint *)&DAT_004ddec4;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  strncpy(&local_8,puVar2,4);
  local_4 = 0;
  iVar5 = _stricmp((byte *)&local_8,&DAT_004ddee0);
  if ((iVar5 != 0) && (iVar5 = _stricmp((byte *)&local_8,&DAT_004ddedc), iVar5 != 0)) {
    stdBitmap_DeCompress((int)bitmap);
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004dded8);
  if (iVar5 == 0) {
    uVar4 = stdLbm_Write((uint)filename,(int)bitmap);
    return (uint)(uVar4 != 0);
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004dded4);
  if (iVar5 == 0) {
    uVar4 = stdPcx_Write((uint)filename,(int)bitmap);
    return (uint)(uVar4 != 0);
  }
  iVar5 = _stricmp((byte *)&local_8,&DAT_004dded0);
  if (iVar5 != 0) {
    iVar5 = _stricmp((byte *)&local_8,&DAT_004ddee0);
    if (iVar5 == 0) {
      iVar5 = stdBitmap_Write(filename,bitmap);
      return (uint)(iVar5 != 0);
    }
    iVar5 = _stricmp((byte *)&local_8,&DAT_004ddedc);
    if (iVar5 != 0) {
      iVar5 = _stricmp((byte *)&local_8,&DAT_004ddecc);
      if (iVar5 != 0) {
        return 0;
      }
      uVar4 = stdBmp_Write((uint)filename,(int)bitmap);
      return (uint)(uVar4 != 0);
    }
    iVar5 = bitmap->nFrames;
    (bitmap->colorFormat).nColorMode = 5;
    iVar3 = 0;
    if (0 < iVar5) {
      do {
        iVar5 = iVar3 + 1;
        (bitmap->ppFrames[iVar3]->format).colorFormat.nColorMode = 5;
        iVar3 = iVar5;
      } while (iVar5 < bitmap->nFrames);
    }
    iVar5 = stdBitmap_Write(filename,bitmap);
    return (uint)(iVar5 != 0);
  }
  uVar4 = stdGif_Write((uint)filename,(int)bitmap);
  return (uint)(uVar4 != 0);
}
#undef local_4
#undef local_8


/* ---- 0x0047aa50  stdBitmap_Load ---- */
/* Grim_ShowSplash loads splash.bm through this Original name stdBitmap_Load (the remaster's
   GrimFandango (Linux): same body (allocate the 0x7c-byte bitmap in Stdbitmap.c, load it from the
   file, free it on failure)); was stdBitmap_LoadResource. */

stdBitmap * __cdecl stdBitmap_Load(char *name,int a,int b)

{
  stdBitmap *a_00;
  void *pvVar1;
  
  a_00 = (stdBitmap *)
         (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df550 + 4);
  if (a_00 != (stdBitmap *)0x0) {
    pvVar1 = stdBitmap_LoadFromFile(name,(int)a_00,a,b);
    if (pvVar1 != (void *)0x0) {
      return a_00;
    }
    (*g_pStd_HS->pFree)(a_00);
  }
  return (stdBitmap *)0x0;
}

/* ---- 0x0047aab0  stdBitmap_LoadFromFile ---- */
/* Stdbitmap.c: opens the file through the main services and reads a BM bitmap */

void * __cdecl stdBitmap_LoadFromFile(char *filename,int a,int b,int c)

{
  uint uVar1;
  void *pvVar2;
  uint *puVar3;
  uint uVar4;
  
  uVar1 = (*g_pStd_HS->pFopen)(filename,&DAT_004ddb18);
  if (uVar1 == 0) {
    return (void *)0x0;
  }
  pvVar2 = (void *)stdBitmap_LoadEntryFromFile(uVar1,a,b,c);
  uVar4 = 0x1f;
  puVar3 = (uint *)stdFileFromPath(filename);
  strncpy((uint *)a,puVar3,uVar4);
  *(undefined1 *)(a + 0x1f) = 0;
  (*g_pStd_HS->pFclose)(uVar1);
  return pvVar2;
}

/* ---- 0x0047ab20  stdBitmap_LoadEntryFromFile ---- */
/* Reads the 'BM  ' header, palette/colour key and the per-mip surfaces (compressed or raw) Original
   name stdBitmap_LoadEntryFromFile (the remaster's GrimFandango (Linux): same body (reads the
   0x80-byte header, magic 'BM  ', version 0x46, then the frames); called by stdBitmap_LoadFromFile
   in both builds); was stdBitmap_LoadBM. */

uint __cdecl stdBitmap_LoadEntryFromFile(uint param_1,int param_2,int param_3,int param_4)

{
  unsigned char _frame[0xf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  VBuffer *surface;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  int *piVar8;
  VBufferFormat *pVVar9;
  ColorFormat *pCVar10;
  void *pvVar11;
  byte *pbVar12;
  #define uStack_e0 (*(uint *)(_frame + (0xf0 - 0xe0)))
  #define uStack_dc (*(uint *)(_frame + (0xf0 - 0xdc)))
  #define pbStack_d8 (*(byte **)(_frame + (0xf0 - 0xd8)))
  #define iStack_d4 (*(int *)(_frame + (0xf0 - 0xd4)))
  #define uStack_d0 (*(uint *)(_frame + (0xf0 - 0xd0)))
  #define local_cc (*(char (*)[4])(_frame + (0xf0 - 0xcc)))
  #define iStack_c8 (*(int *)(_frame + (0xf0 - 0xc8)))
  #define uStack_c4 (*(uint *)(_frame + (0xf0 - 0xc4)))
  #define uStack_c0 (*(uint *)(_frame + (0xf0 - 0xc0)))
  #define uStack_bc (*(uint *)(_frame + (0xf0 - 0xbc)))
  #define uStack_b8 (*(undefined4 *)(_frame + (0xf0 - 0xb8)))
  #define uStack_b4 (*(undefined4 *)(_frame + (0xf0 - 0xb4)))
  #define uStack_b0 (*(undefined4 *)(_frame + (0xf0 - 0xb0)))
  #define auStack_ac (*(undefined4 (*)[24])(_frame + (0xf0 - 0xac)))
  #define VStack_4c (*(VBufferFormat *)(_frame + (0xf0 - 0x4c)))
  
  (*g_pStd_HS->pFread)(param_1,local_cc,0x80);
  uVar2 = strncmp(local_cc,&DAT_004df5a0,4);
  if (uVar2 != 0) {
    return 0;
  }
  if (iStack_c8 == 0x46) {
    stdBitmap_NewEntry((undefined4 *)param_2,uStack_bc,0,uStack_c4,uStack_c0,auStack_ac);
    *(undefined4 *)(param_2 + 0x6c) = uStack_b8;
    *(undefined4 *)(param_2 + 0x74) = uStack_b0;
    pVVar9 = &VStack_4c;
    for (iVar5 = 0x13; iVar5 != 0; iVar5 = iVar5 + -1) {
      pVVar9->nWidth = 0;
      pVVar9 = (VBufferFormat *)&pVVar9->nHeight;
    }
    uStack_e0 = 0;
    *(undefined4 *)(param_2 + 0x70) = uStack_b4;
    if (*(int *)(param_2 + 100) != 0) {
      do {
        (*g_pStd_HS->pFread)(param_1,&iStack_d4,8);
        VStack_4c.nHeight = uStack_d0;
        VStack_4c.nWidth = iStack_d4;
        piVar8 = (int *)(param_2 + 0x28);
        pCVar10 = &VStack_4c.colorFormat;
        for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
          pCVar10->nColorMode = *piVar8;
          piVar8 = piVar8 + 1;
          pCVar10 = (ColorFormat *)&pCVar10->nBpp;
        }
        surface = stdDisplay_VBufferNew(&VStack_4c,param_3,param_4,0);
        if (surface == (VBuffer *)0x0) {
          return 0;
        }
        stdBitmap_SetSurface(param_2,uStack_e0,(uint)surface);
        stdDisplay_VBufferLock(surface);
        iVar5 = *(int *)(param_2 + 0x20);
        if (iVar5 == 0) {
          uVar2 = (surface->format).colorFormat.nBpp;
          pvVar11 = surface->pPixels;
          uVar7 = 0;
          iVar5 = (surface->format).nWidth;
          if (uStack_d0 != 0) {
            do {
              (*g_pStd_HS->pFread)(param_1,pvVar11,(uVar2 >> 3) * iVar5);
              pvVar11 = (void *)((int)pvVar11 + (surface->format).nPitch);
              uVar7 = uVar7 + 1;
            } while (uVar7 < uStack_d0);
          }
        }
        else if (iVar5 == 1) {
          pbVar6 = surface->pPixels;
          pbStack_d8 = pbVar6;
          if ((surface->format).dwSize != 0) {
            do {
              uVar2 = stdFGetc(param_1);
              if (((byte)uVar2 & 0xc0) == 0xc0) {
                uVar7 = uVar2 & 0x3f;
                uVar3 = stdFGetc(param_1);
                bVar1 = (byte)uVar3;
                if (uVar7 != 0) {
                  pbVar12 = pbVar6;
                  for (uVar3 = uVar7 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                    *(uint *)pbVar12 = CONCAT22(CONCAT11(bVar1,bVar1),CONCAT11(bVar1,bVar1));
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar6 = pbStack_d8 + uVar7;
                  for (uVar2 = uVar2 & 3; pbStack_d8 = pbVar6, uVar2 != 0; uVar2 = uVar2 - 1) {
                    *pbVar12 = bVar1;
                    pbVar12 = pbVar12 + 1;
                  }
                }
              }
              else {
                *pbVar6 = (byte)uVar2;
                pbVar6 = pbVar6 + 1;
                pbStack_d8 = pbVar6;
              }
            } while ((uint)((int)pbVar6 - (int)surface->pPixels) < (surface->format).dwSize);
          }
        }
        else if ((iVar5 == 3) &&
                ((*g_pStd_HS->pFread)(param_1,&uStack_dc,4), uStack_dc < (surface->format).dwSize))
        {
          pvVar4 = (void *)(*g_pStd_HS->pAlloc)
                                     (uStack_dc,s_C__grimjedi_Libs_Std_General_Std_004df574,
                                      DAT_004df558 + 0x82);
          (*g_pStd_HS->pFread)(param_1,pvVar4,uStack_dc);
          pvVar11 = surface->pPixels;
          surface->nType = 2;
          (surface->format).dwSize = uStack_dc;
          (*g_pStd_HS->pFree)(pvVar11);
          surface->pPixels = pvVar4;
        }
        stdDisplay_VBufferUnlock(surface);
        if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
          stdDisplay_VBufferSetColorKey(surface,*(int *)(param_2 + 0x74));
        }
        uStack_e0 = uStack_e0 + 1;
      } while (uStack_e0 < *(uint *)(param_2 + 100));
    }
    if ((*(byte *)(param_2 + 0x24) & 2) != 0) {
      iVar5 = (*g_pStd_HS->pAlloc)
                        (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df558 + 0x98);
      *(int *)(param_2 + 0x60) = iVar5;
      if (iVar5 == 0) {
        return 0;
      }
      (*g_pStd_HS->pFread)(param_1,iVar5,0x300);
    }
    return 1;
  }
  return 0;
}
#undef VStack_4c
#undef auStack_ac
#undef iStack_c8
#undef iStack_d4
#undef local_cc
#undef pbStack_d8
#undef uStack_b0
#undef uStack_b4
#undef uStack_b8
#undef uStack_bc
#undef uStack_c0
#undef uStack_c4
#undef uStack_d0
#undef uStack_dc
#undef uStack_e0


/* ---- 0x0047ae70  stdBitmap_Free ---- */
void __cdecl stdBitmap_Free(stdBitmap *bitmap)

{
  stdBitmap_FreeEntry((int)bitmap);
  (*g_pStd_HS->pFree)(bitmap);
  return;
}

/* ---- 0x0047ae90  stdBitmap_FreeEntry ---- */
/* Frees the surface array at +0x78 (+0x64 count) Original name stdBitmap_FreeEntry (the remaster's
   GrimFandango (Linux): same body (stdDisplay_VBufferFree of every frame, free the frame array at
   +0x78)); was stdBitmap_FreeSurfaces. */

void __cdecl stdBitmap_FreeEntry(int param_1)

{
  VBuffer *surface;
  uint uVar1;
  
  if (*(int *)(param_1 + 0x78) != 0) {
    uVar1 = 0;
    if (*(int *)(param_1 + 100) != 0) {
      do {
        surface = *(VBuffer **)(*(int *)(param_1 + 0x78) + uVar1 * 4);
        if (surface != (VBuffer *)0x0) {
          stdDisplay_VBufferFree(surface);
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_1 + 100));
    }
    (*g_pStd_HS->pFree)(*(undefined4 *)(param_1 + 0x78));
  }
  if (*(int *)(param_1 + 0x60) != 0) {
    (*g_pStd_HS->pFree)(*(int *)(param_1 + 0x60));
  }
  return;
}

/* ---- 0x0047aef0  stdBitmap_AppendToFile ---- */
/* Writes a BM bitmap (header, palette, surfaces) via stdFile Original name stdBitmap_AppendToFile
   (the remaster's GrimFandango (Linux): same body (the 0x80-byte "BM  " version 0x46 header, then
   the frames); called by stdBitmap_Write in both builds); was stdBitmap_WriteBM. */

uint __cdecl stdBitmap_AppendToFile(uint param_1,int param_2)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  undefined3 uVar9;
  undefined3 extraout_var;
  undefined4 *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  int iVar13;
  uint uVar14;
  #define uStack_a4 (*(uint *)(_frame + (0xc0 - 0xa4)))
  #define uStack_a0 (*(uint *)(_frame + (0xc0 - 0xa0)))
  #define uStack_9c (*(undefined4 *)(_frame + (0xc0 - 0x9c)))
  #define uStack_98 (*(uint *)(_frame + (0xc0 - 0x98)))
  #define iStack_94 (*(int *)(_frame + (0xc0 - 0x94)))
  #define uStack_90 (*(uint *)(_frame + (0xc0 - 0x90)))
  #define uStack_8c (*(uint *)(_frame + (0xc0 - 0x8c)))
  #define iStack_88 (*(int *)(_frame + (0xc0 - 0x88)))
  #define uStack_84 (*(uint *)(_frame + (0xc0 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0xc0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xc0 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0xc0 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0xc0 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0xc0 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0xc0 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0xc0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xc0 - 0x64)))
  #define local_60 (*(undefined4 (*)[24])(_frame + (0xc0 - 0x60)))
  
  puVar11 = &local_80;
  for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  strncpy(&local_80,(uint *)&DAT_004df5a0,4);
  local_7c = 0x46;
  local_78 = *(uint *)(param_2 + 0x20);
  local_74 = *(uint *)(param_2 + 0x24);
  local_70 = *(uint *)(param_2 + 100);
  local_6c = *(uint *)(param_2 + 0x6c);
  local_68 = *(uint *)(param_2 + 0x70);
  local_64 = *(uint *)(param_2 + 0x74);
  puVar10 = (undefined4 *)(param_2 + 0x28);
  puVar12 = local_60;
  for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  iVar7 = (*g_pStd_HS->pFwrite)(param_1,&local_80,0x80);
  if (iVar7 != 0x80) {
    return 0;
  }
  iVar7 = 0;
  uStack_98 = 0;
  if (*(int *)(param_2 + 100) != 0) {
    do {
      piVar3 = (int *)(*(int *)(param_2 + 0x78) + iVar7);
      iStack_94 = *(int *)(*piVar3 + 0xc);
      uStack_90 = *(uint *)(*piVar3 + 0x10);
      iVar4 = (*g_pStd_HS->pFwrite)(param_1,&iStack_94,8);
      if (iVar4 != 8) {
        return 0;
      }
      if (local_78 == 0) {
        stdDisplay_VBufferLock(*(VBuffer **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_a4 = 0;
        iVar4 = *(int *)(iVar7 + *(int *)(param_2 + 0x78));
        iVar13 = *(int *)(iVar4 + 0x5c);
        iVar4 = (*(uint *)(iVar4 + 0x24) >> 3) * iStack_94;
        if (uStack_90 != 0) {
          do {
            iVar5 = (*g_pStd_HS->pFwrite)(param_1,iVar13,iVar4);
            if (iVar5 != iVar4) {
              return 0;
            }
            iVar13 = iVar13 + *(int *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x18);
            uStack_a4 = uStack_a4 + 1;
          } while (uStack_a4 < uStack_90);
        }
        stdDisplay_VBufferUnlock(*(VBuffer **)(iVar7 + *(int *)(param_2 + 0x78)));
      }
      else if (local_78 == 1) {
        iVar4 = *(int *)(param_2 + 0x78);
        uStack_8c = 0;
        iStack_88 = *(int *)(*(int *)(iVar7 + iVar4) + 0x5c);
        if (*(int *)(*(int *)(iVar7 + iVar4) + 0x10) != 0) {
          do {
            iVar13 = *(int *)(*(int *)(iVar7 + iVar4) + 0xc);
            iVar5 = uStack_8c * iVar13 + iStack_88;
            uVar14 = 0;
            if (iVar13 != 0) {
              do {
                pbVar1 = (byte *)(iVar5 + uVar14);
                uVar9 = (undefined3)((uint)iVar13 >> 8);
                bVar8 = 1;
                bVar2 = *pbVar1;
                uStack_a0 = 1;
                if (bVar2 == *(byte *)(uVar14 + 1 + iVar5)) {
                  uVar6 = 1;
                  uStack_84 = *(uint *)(*(int *)(iVar7 + iVar4) + 0xc);
                  do {
                    if ((uStack_84 <= uVar6 + uVar14) || (0x3e < bVar8)) break;
                    bVar8 = bVar8 + 1;
                    uStack_a0 = (uint)bVar8;
                    uVar6 = (uint)bVar8;
                  } while (bVar2 == pbVar1[uVar6]);
                }
                if ((1 < bVar8) || (0xbf < bVar2)) {
                  stdFPutc(CONCAT31(uVar9,bVar8) | 0xc0,param_1);
                  uVar9 = extraout_var;
                }
                stdFPutc(CONCAT31(uVar9,*pbVar1),param_1);
                uVar14 = uVar14 + uStack_a0;
                iVar4 = *(int *)(param_2 + 0x78);
                iVar13 = *(int *)(iVar7 + iVar4);
              } while (uVar14 < *(uint *)(iVar13 + 0xc));
            }
            iVar4 = *(int *)(param_2 + 0x78);
            uStack_8c = uStack_8c + 1;
          } while (uStack_8c < *(uint *)(*(int *)(iVar4 + iVar7) + 0x10));
        }
      }
      else if (local_78 == 3) {
        stdDisplay_VBufferLock(*(VBuffer **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_9c = *(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x14);
        (*g_pStd_HS->pFwrite)(param_1,&uStack_9c,4);
        (*g_pStd_HS->pFwrite)
                  (param_1,*(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x5c),
                   uStack_9c);
        stdDisplay_VBufferUnlock(*(VBuffer **)(iVar7 + *(int *)(param_2 + 0x78)));
      }
      uStack_98 = uStack_98 + 1;
      iVar7 = iVar7 + 4;
    } while (uStack_98 < *(uint *)(param_2 + 100));
  }
  if (((*(byte *)(param_2 + 0x24) & 2) != 0) &&
     (iVar7 = (*g_pStd_HS->pFwrite)(param_1,*(undefined4 *)(param_2 + 0x60),0x300), iVar7 != 0x300))
  {
    return 0;
  }
  return 1;
}
#undef iStack_88
#undef iStack_94
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74
#undef local_78
#undef local_7c
#undef local_80
#undef uStack_84
#undef uStack_8c
#undef uStack_90
#undef uStack_98
#undef uStack_9c
#undef uStack_a0
#undef uStack_a4


/* ---- 0x0047b250  stdBitmap_Write ---- */
/* Original name stdBitmap_Write (the remaster's GrimFandango (Linux): same body (open the file for
   writing, stdBitmap_AppendToFile, close); stdWriteImage's "bm" case in both builds); was
   stdBitmap_SaveBM. */

int __cdecl stdBitmap_Write(char *filename,void *bitmap)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (*g_pStd_HS->pFopen)(filename,&DAT_004ddb1c);
  if (uVar1 == 0) {
    return 0;
  }
  uVar2 = stdBitmap_AppendToFile(uVar1,(int)bitmap);
  if (uVar2 == 0) {
    (*g_pStd_HS->pFclose)();
    return 0;
  }
  (*g_pStd_HS->pFclose)(uVar1);
  return 1;
}

/* ---- 0x0047b2b0  stdBitmap_ConvertColorFormat ---- */
/* Deep copy of a 0x7c-byte bitmap record including its surfaces Original name
   stdBitmap_ConvertColorFormat (the remaster's GrimFandango (Linux): aligned call in
   sputRender_SaveDrawBuffer, sputRender_SaveScreen); was stdBitmap_CopyFrom. */

void __cdecl stdBitmap_ConvertColorFormat(int *param_1,int param_2)

{
  VBuffer *pVVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  
  piVar5 = (int *)(param_2 + 0x28);
  iVar2 = 0x38;
  bVar6 = true;
  piVar3 = param_1;
  piVar4 = piVar5;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar6 = (char)*piVar3 == (char)*piVar4;
    piVar3 = (int *)((int)piVar3 + 1);
    piVar4 = (int *)((int)piVar4 + 1);
  } while (bVar6);
  if ((!bVar6) && ((*piVar5 != 0 || (*param_1 != 0)))) {
    iVar2 = 0;
    if (0 < *(int *)(param_2 + 100)) {
      do {
        pVVar1 = *(VBuffer **)(*(int *)(param_2 + 0x78) + iVar2 * 4);
        if (pVVar1->nType != 2) {
          pVVar1 = stdDisplay_VBufferConvertColorFormat((ColorFormat *)param_1,pVVar1);
          *(VBuffer **)(*(int *)(param_2 + 0x78) + iVar2 * 4) = pVVar1;
          if (*(int *)(*(int *)(param_2 + 0x78) + iVar2 * 4) == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_a_new_frame_w_004df5a8,
                       s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df55c + 0x15);
          }
          if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
            pVVar1 = *(VBuffer **)(*(int *)(param_2 + 0x78) + iVar2 * 4);
            stdDisplay_VBufferSetColorKey(pVVar1,pVVar1->dwColorKey);
          }
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(param_2 + 100));
    }
    if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
      iVar2 = stdColor_ColorConvertOnePixel((int)param_1,*(uint *)(param_2 + 0x74),(int)piVar5);
      *(int *)(param_2 + 0x74) = iVar2;
    }
    for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *param_1;
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    }
  }
  return;
}

/* ---- 0x0047b380  stdBitmap_VBufferToBitmap ---- */
/* Allocates a new bitmap and blits every surface into the requested pixel format Original name
   stdBitmap_VBufferToBitmap (the remaster's GrimFandango (Linux): aligned call in
   sputRender_SaveDrawBuffer, sputRender_SaveScreen); was stdBitmap_Convert. */

stdBitmap * __cdecl stdBitmap_VBufferToBitmap(VBuffer *vbuf,int format,int flags)

{
  uint uVar1;
  stdBitmap *psVar2;
  VBuffer **ppVVar3;
  VBuffer *pVVar4;
  undefined4 *puVar5;
  int iVar6;
  ColorFormat *pCVar7;
  undefined4 *puVar8;
  ColorFormat *pCVar9;
  
  psVar2 = (stdBitmap *)
           (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 4);
  psVar2->nType = 0;
  if (vbuf->pPalette == (void *)0x0) {
    psVar2->dwPalFlags = 0;
  }
  else {
    psVar2->dwPalFlags = 2;
  }
  psVar2->nFrames = 1;
  psVar2->nCurFrame = 0;
  psVar2->nX = 0;
  psVar2->nY = 0;
  ppVVar3 = (VBuffer **)
            (*g_pStd_HS->pAlloc)(4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 0x14);
  psVar2->ppFrames = ppVVar3;
  if (ppVVar3 == (VBuffer **)0x0) {
    return (stdBitmap *)0x0;
  }
  pVVar4 = stdDisplay_VBufferNew(&vbuf->format,format,flags,0);
  *psVar2->ppFrames = pVVar4;
  if (*psVar2->ppFrames == (VBuffer *)0x0) {
    return (stdBitmap *)0x0;
  }
  Surface_Blit(*psVar2->ppFrames,vbuf,0,0,(int *)0x0,0);
  stdDisplay_VBufferUnlock(vbuf);
  uVar1 = psVar2->dwPalFlags;
  pCVar7 = &((*psVar2->ppFrames)->format).colorFormat;
  pCVar9 = &psVar2->colorFormat;
  for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1) {
    pCVar9->nColorMode = pCVar7->nColorMode;
    pCVar7 = (ColorFormat *)&pCVar7->nBpp;
    pCVar9 = (ColorFormat *)&pCVar9->nBpp;
  }
  if ((uVar1 & 2) != 0) {
    puVar5 = (undefined4 *)
             (*g_pStd_HS->pAlloc)
                       (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 0x29);
    psVar2->pPalette = puVar5;
    if (puVar5 == (undefined4 *)0x0) {
      return (stdBitmap *)0x0;
    }
    puVar8 = vbuf->pPalette;
    for (iVar6 = 0xc0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar5 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
    }
    return psVar2;
  }
  psVar2->pPalette = (void *)0x0;
  return psVar2;
}

/* ---- 0x0047b4b0  stdBitmap_NewEntry ---- */
/* Zeroes the 0x7c-byte record and stores the format/size/surface count Original name
   stdBitmap_NewEntry (the remaster's GrimFandango (Linux): same parameters (bitmap, frame count,
   ...) and body (clear the 0x7c-byte record, allocate the frame array in Stdbitmap.c)); was
   stdBitmap_Init. */

uint __cdecl
stdBitmap_NewEntry(undefined4 *param_1,uint param_2,uint param_3,uint param_4,uint param_5,
                  undefined4 *param_6)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = param_1;
  for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  puVar1 = (undefined4 *)
           (*g_pStd_HS->pAlloc)
                     (param_2 * 4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df570 + 0xb);
  param_1[0x1e] = puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (uVar3 = param_2 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar1 = 0;
    puVar1 = (undefined4 *)((int)puVar1 + 1);
  }
  param_1[9] = param_5;
  param_1[8] = param_4;
  puVar1 = param_1 + 10;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *param_6;
    param_6 = param_6 + 1;
    puVar1 = puVar1 + 1;
  }
  param_1[0x19] = param_2;
  param_1[0x18] = param_3;
  return 1;
}

/* ---- 0x0047b540  stdBitmap_SetSurface ---- */
void __cdecl stdBitmap_SetSurface(int param_1,int param_2,uint param_3)

{
  *(uint *)(*(int *)(param_1 + 0x78) + param_2 * 4) = param_3;
  return;
}

/* ---- 0x0047b560  stdBitmap_MemUsage ---- */
/* Original name stdBitmap_MemUsage (the remaster's GrimFandango (Linux): same body (0x7c plus the
   size +0x14 of every frame whose +8 is 0): the bitmap's memory use, not a conversion; called by
   the background handler, sputRoom_LoadResources and ObjectStateImage_Load in both builds); was
   stdBitmap_ConvertToDisplay. */

int __cdecl stdBitmap_MemUsage(stdBitmap *bitmap)

{
  VBuffer **ppVVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = bitmap->nFrames;
  if (0 < iVar3) {
    ppVVar1 = bitmap->ppFrames;
    do {
      if ((*ppVVar1)->nVideoMemory == 0) {
        iVar2 = iVar2 + ((*ppVVar1)->format).dwSize;
      }
      ppVVar1 = ppVVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return iVar2 + 0x7c;
}

/* ---- 0x0047b590  stdBitmap_DeCompress ---- */
/* Original name stdBitmap_DeCompress (the remaster's GrimFandango (Linux): aligned call in
   stdLoadImage, stdWriteImage); was stdBitmap_DecompressAll. */

void __cdecl stdBitmap_DeCompress(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 100)) {
    do {
      stdDisplay_VBufferDeCompress(*(VBuffer **)(*(int *)(param_1 + 0x78) + iVar1 * 4));
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 100));
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}

/* ---- 0x0047b5f0  stdPalEffects_ResetEffect ---- */
/* Zeroes 10 dwords and sets the gamma/scale field to 1.0 Original name stdPalEffects_ResetEffect
   (the remaster's GrimFandango (Linux): the call on rdroid_curColorEffects in rdOpen, same body
   (ten words cleared, +0x24 = 1.0f)); was stdBitmap_InitHeader. */

void __cdecl stdPalEffects_ResetEffect(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[9] = 0x3f800000;
  return;
}
