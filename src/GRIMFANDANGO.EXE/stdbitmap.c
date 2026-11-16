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

stdBitmap * __cdecl stdLoadImage(char *filename,int videoMem,int b)

{
  stdBitmap *bitmap;
  
  bitmap = stdLoadImageData(filename,videoMem,b);
  if (bitmap != (stdBitmap *)0x0) {
    stdBitmap_DeCompress((int)bitmap);
  }
  return bitmap;
}

/* ---- 0x00473660  stdLoadImageData ---- */
/* Original name stdLoadImageData (the remaster's GrimFandango (Linux): strings: '.bm' | '.pic' |
   '.zbm' | '.gif'); was stdBitmap_LoadFile. */

stdBitmap * __cdecl stdLoadImageData(char *name,int a,int b)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  stdBitmap *psVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  #define local_8 (*(char (*)[8])(_frame + (0x20 - 0x8)))
  
  pcVar2 = strrchr(name,'.');
  if ((uint *)pcVar2 == (uint *)0x0) {
    uVar4 = 0xffffffff;
    pcVar2 = s__lbm_004ddec4;
    do {
      pcVar7 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = name;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar7 + -uVar4;
    pcVar8 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    pcVar2 = s__lbm_004ddec4;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  strncpy((uint *)local_8,(uint *)pcVar2,4);
  local_8[4] = '\0';
  iVar5 = _stricmp((byte *)local_8,(byte *)s__lbm_004ddec4);
  if (iVar5 == 0) {
    psVar3 = stdLbm_Load(name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s__pcx_004ddebc);
  if (iVar5 == 0) {
    psVar3 = (stdBitmap *)stdPcx_Load((uint)name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s__gif_004ddeb4);
  if (iVar5 == 0) {
    psVar3 = stdGif_Load(name,a,b);
    return psVar3;
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s__bm_004ddeb0);
  if ((iVar5 != 0) && (iVar5 = _stricmp((byte *)local_8,(byte *)s__zbm_004ddea8), iVar5 != 0)) {
    iVar5 = _stricmp((byte *)local_8,(byte *)s__pic_004ddea0);
    if (iVar5 == 0) {
      psVar3 = (stdBitmap *)stdPic_Load((uint)name,a,b);
      return psVar3;
    }
    iVar5 = _stricmp((byte *)local_8,(byte *)s__bmp_004dde98);
    if (iVar5 != 0) {
      return (stdBitmap *)0x0;
    }
    psVar3 = (stdBitmap *)stdBmp_Load((uint)name,a,b);
    return psVar3;
  }
  psVar3 = stdBitmap_Load(name,a,b);
  return psVar3;
}
#undef local_8


/* ---- 0x00473810  stdWriteImage ---- */
/* Picks the writer from the file extension: .bm/.zbm (stdBitmap_Write, zbm marks format 5), .bmp,
   .gif, .pcx, .lbm Original name stdWriteImage (the remaster's GrimFandango (Linux): strings: 'lbm'
   | 'pcx' | 'zbm' | 'bmp'); was stdBitmap_SaveByExtension. */

int __cdecl stdWriteImage(char *filename,stdBitmap *bitmap)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  #define local_8 (*(char (*)[8])(_frame + (0x20 - 0x8)))
  
  pcVar2 = stdFnames_FindExt(filename);
  if ((uint *)pcVar2 == (uint *)0x0) {
    uVar4 = 0xffffffff;
    pcVar2 = s__lbm_004ddec4;
    do {
      pcVar7 = pcVar2;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar2 = filename;
    do {
      pcVar8 = pcVar2;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar8 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar7 + -uVar4;
    pcVar8 = pcVar8 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    pcVar2 = s__lbm_004ddec4;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  strncpy((uint *)local_8,(uint *)pcVar2,4);
  local_8[4] = '\0';
  iVar5 = _stricmp((byte *)local_8,(byte *)s_bm_004ddee0);
  if ((iVar5 != 0) && (iVar5 = _stricmp((byte *)local_8,(byte *)s_zbm_004ddedc), iVar5 != 0)) {
    stdBitmap_DeCompress((int)bitmap);
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s_lbm_004dded8);
  if (iVar5 == 0) {
    uVar4 = stdLbm_Write((uint)filename,(int)bitmap);
    return (uint)(uVar4 != 0);
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s_pcx_004dded4);
  if (iVar5 == 0) {
    uVar4 = stdPcx_Write((uint)filename,(int)bitmap);
    return (uint)(uVar4 != 0);
  }
  iVar5 = _stricmp((byte *)local_8,(byte *)s_gif_004dded0);
  if (iVar5 != 0) {
    iVar5 = _stricmp((byte *)local_8,(byte *)s_bm_004ddee0);
    if (iVar5 == 0) {
      iVar5 = stdBitmap_Write(filename,bitmap);
      return (uint)(iVar5 != 0);
    }
    iVar5 = _stricmp((byte *)local_8,(byte *)s_zbm_004ddedc);
    if (iVar5 != 0) {
      iVar5 = _stricmp((byte *)local_8,(byte *)s_bmp_004ddecc);
      if (iVar5 != 0) {
        return 0;
      }
      uVar4 = stdBmp_Write(filename,bitmap);
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
  uint f;
  void *pvVar1;
  uint *puVar2;
  uint uVar3;
  
  f = (*g_pStd_HS->pFopen)(filename,s_rb_004ddb18);
  if (f == 0) {
    return (void *)0x0;
  }
  pvVar1 = (void *)stdBitmap_LoadEntryFromFile(f,a,b,c);
  uVar3 = 0x1f;
  puVar2 = (uint *)stdFileFromPath(filename);
  strncpy((uint *)a,puVar2,uVar3);
  *(undefined1 *)(a + 0x1f) = 0;
  (*g_pStd_HS->pFclose)(f);
  return pvVar1;
}

/* ---- 0x0047ab20  stdBitmap_LoadEntryFromFile ---- */
/* Reads the 'BM  ' header, palette/colour key and the per-mip surfaces (compressed or raw) Original
   name stdBitmap_LoadEntryFromFile (the remaster's GrimFandango (Linux): same body (reads the
   0x80-byte header, magic 'BM  ', version 0x46, then the frames); called by stdBitmap_LoadFromFile
   in both builds); was stdBitmap_LoadBM. */

uint __cdecl stdBitmap_LoadEntryFromFile(uint f,int a,int videoMem,int b)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  uint uStack_e0;
  uint uStack_dc;
  byte *pbStack_d8;
  BmFrameHeader frame;
  BmHeader header;
  #define VStack_4c (*(VBufferFormat *)(_frame + (0x60 - 0x4c)))
  
  (*g_pStd_HS->pFread)(f,&header,0x80);
  uVar2 = strncmp(header.aMagic,s_BM_004df5a0,4);
  if (uVar2 != 0) {
    return 0;
  }
  if (header.nVersion == 0x46) {
    stdBitmap_NewEntry((undefined4 *)a,header.nFrames,0,header.nType,header.dwPalFlags,
                       &header.colorFormat.nColorMode);
    *(int *)(a + 0x6c) = header.nX;
    *(uint *)(a + 0x74) = header.dwColorKey;
    pVVar9 = &VStack_4c;
    for (iVar5 = 0x13; iVar5 != 0; iVar5 = iVar5 + -1) {
      pVVar9->nWidth = 0;
      pVVar9 = (VBufferFormat *)&pVVar9->nHeight;
    }
    uStack_e0 = 0;
    *(int *)(a + 0x70) = header.nY;
    if (*(int *)(a + 100) != 0) {
      do {
        (*g_pStd_HS->pFread)(f,&frame,8);
        VStack_4c.nHeight = frame.nHeight;
        VStack_4c.nWidth = frame.nWidth;
        piVar8 = (int *)(a + 0x28);
        pCVar10 = &VStack_4c.colorFormat;
        for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
          pCVar10->nColorMode = *piVar8;
          piVar8 = piVar8 + 1;
          pCVar10 = (ColorFormat *)&pCVar10->nBpp;
        }
        surface = stdDisplay_VBufferNew(&VStack_4c,videoMem,b,0);
        if (surface == (VBuffer *)0x0) {
          return 0;
        }
        stdBitmap_SetSurface(a,uStack_e0,(uint)surface);
        stdDisplay_VBufferLock(surface);
        iVar5 = *(int *)(a + 0x20);
        if (iVar5 == 0) {
          uVar2 = (surface->format).colorFormat.nBpp;
          pvVar11 = surface->pPixels;
          uVar7 = 0;
          iVar5 = (surface->format).nWidth;
          if (frame.nHeight != 0) {
            do {
              (*g_pStd_HS->pFread)(f,pvVar11,(uVar2 >> 3) * iVar5);
              pvVar11 = (void *)((int)pvVar11 + (surface->format).nPitch);
              uVar7 = uVar7 + 1;
            } while (uVar7 < (uint)frame.nHeight);
          }
        }
        else if (iVar5 == 1) {
          pbVar6 = surface->pPixels;
          pbStack_d8 = pbVar6;
          if ((surface->format).dwSize != 0) {
            do {
              uVar2 = stdFGetc(f);
              if (((byte)uVar2 & 0xc0) == 0xc0) {
                uVar7 = uVar2 & 0x3f;
                uVar3 = stdFGetc(f);
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
                ((*g_pStd_HS->pFread)(f,&uStack_dc,4), uStack_dc < (surface->format).dwSize)) {
          pvVar4 = (void *)(*g_pStd_HS->pAlloc)
                                     (uStack_dc,s_C__grimjedi_Libs_Std_General_Std_004df574,
                                      DAT_004df558 + 0x82);
          (*g_pStd_HS->pFread)(f,pvVar4,uStack_dc);
          pvVar11 = surface->pPixels;
          surface->nType = 2;
          (surface->format).dwSize = uStack_dc;
          (*g_pStd_HS->pFree)(pvVar11);
          surface->pPixels = pvVar4;
        }
        stdDisplay_VBufferUnlock(surface);
        if ((*(byte *)(a + 0x24) & 1) != 0) {
          stdDisplay_VBufferSetColorKey(surface,*(int *)(a + 0x74));
        }
        uStack_e0 = uStack_e0 + 1;
      } while (uStack_e0 < *(uint *)(a + 100));
    }
    if ((*(byte *)(a + 0x24) & 2) != 0) {
      iVar5 = (*g_pStd_HS->pAlloc)
                        (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df558 + 0x98);
      *(int *)(a + 0x60) = iVar5;
      if (iVar5 == 0) {
        return 0;
      }
      (*g_pStd_HS->pFread)(f,iVar5,0x300);
    }
    return 1;
  }
  return 0;
}
#undef VStack_4c


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

void __cdecl stdBitmap_FreeEntry(int bitmap)

{
  VBuffer *surface;
  uint uVar1;
  
  if (*(int *)(bitmap + 0x78) != 0) {
    uVar1 = 0;
    if (*(int *)(bitmap + 100) != 0) {
      do {
        surface = *(VBuffer **)(*(int *)(bitmap + 0x78) + uVar1 * 4);
        if (surface != (VBuffer *)0x0) {
          stdDisplay_VBufferFree(surface);
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(bitmap + 100));
    }
    (*g_pStd_HS->pFree)(*(undefined4 *)(bitmap + 0x78));
  }
  if (*(int *)(bitmap + 0x60) != 0) {
    (*g_pStd_HS->pFree)(*(int *)(bitmap + 0x60));
  }
  return;
}

/* ---- 0x0047aef0  stdBitmap_AppendToFile ---- */
/* Writes a BM bitmap (header, palette, surfaces) via stdFile Original name stdBitmap_AppendToFile
   (the remaster's GrimFandango (Linux): same body (the 0x80-byte "BM  " version 0x46 header, then
   the frames); called by stdBitmap_Write in both builds); was stdBitmap_WriteBM. */

uint __cdecl stdBitmap_AppendToFile(uint f,int bitmap)

{
  byte *pbVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte bVar9;
  undefined3 uVar10;
  undefined3 extraout_var;
  BmHeader *pBVar11;
  ColorFormat *pCVar12;
  int iVar13;
  uint uVar14;
  uint uStack_a4;
  uint uStack_a0;
  undefined4 uStack_9c;
  uint uStack_98;
  BmFrameHeader frame;
  uint uStack_8c;
  BmHeader header;
  
  pBVar11 = &header;
  for (iVar8 = 0x20; iVar8 != 0; iVar8 = iVar8 + -1) {
    pBVar11->aMagic[0] = '\0';
    pBVar11->aMagic[1] = '\0';
    pBVar11->aMagic[2] = '\0';
    pBVar11->aMagic[3] = '\0';
    pBVar11 = (BmHeader *)&pBVar11->nVersion;
  }
  strncpy((uint *)&header,(uint *)s_BM_004df5a0,4);
  header.nVersion = 0x46;
  header.nType = *(int *)(bitmap + 0x20);
  header.dwPalFlags = *(uint *)(bitmap + 0x24);
  header.nFrames = *(int *)(bitmap + 100);
  header.nX = *(int *)(bitmap + 0x6c);
  header.nY = *(int *)(bitmap + 0x70);
  header.dwColorKey = *(uint *)(bitmap + 0x74);
  piVar3 = (int *)(bitmap + 0x28);
  pCVar12 = &header.colorFormat;
  for (iVar8 = 0xe; iVar8 != 0; iVar8 = iVar8 + -1) {
    pCVar12->nColorMode = *piVar3;
    piVar3 = piVar3 + 1;
    pCVar12 = (ColorFormat *)&pCVar12->nBpp;
  }
  iVar8 = (*g_pStd_HS->pFwrite)(f,&header,0x80);
  if (iVar8 != 0x80) {
    return 0;
  }
  iVar8 = 0;
  uStack_98 = 0;
  if (*(int *)(bitmap + 100) != 0) {
    do {
      piVar3 = (int *)(*(int *)(bitmap + 0x78) + iVar8);
      frame.nWidth = *(int *)(*piVar3 + 0xc);
      frame.nHeight = *(int *)(*piVar3 + 0x10);
      iVar4 = (*g_pStd_HS->pFwrite)(f,&frame,8);
      if (iVar4 != 8) {
        return 0;
      }
      if (header.nType == 0) {
        stdDisplay_VBufferLock(*(VBuffer **)(iVar8 + *(int *)(bitmap + 0x78)));
        uStack_a4 = 0;
        iVar4 = *(int *)(iVar8 + *(int *)(bitmap + 0x78));
        iVar13 = *(int *)(iVar4 + 0x5c);
        iVar4 = (*(uint *)(iVar4 + 0x24) >> 3) * frame.nWidth;
        if (frame.nHeight != 0) {
          do {
            iVar5 = (*g_pStd_HS->pFwrite)(f,iVar13,iVar4);
            if (iVar5 != iVar4) {
              return 0;
            }
            iVar13 = iVar13 + *(int *)(*(int *)(iVar8 + *(int *)(bitmap + 0x78)) + 0x18);
            uStack_a4 = uStack_a4 + 1;
          } while (uStack_a4 < (uint)frame.nHeight);
        }
        stdDisplay_VBufferUnlock(*(VBuffer **)(iVar8 + *(int *)(bitmap + 0x78)));
      }
      else if (header.nType == 1) {
        iVar13 = *(int *)(bitmap + 0x78);
        uStack_8c = 0;
        iVar4 = *(int *)(*(int *)(iVar8 + iVar13) + 0x5c);
        if (*(int *)(*(int *)(iVar8 + iVar13) + 0x10) != 0) {
          do {
            iVar5 = *(int *)(*(int *)(iVar8 + iVar13) + 0xc);
            iVar6 = uStack_8c * iVar5 + iVar4;
            uVar14 = 0;
            if (iVar5 != 0) {
              do {
                pbVar1 = (byte *)(iVar6 + uVar14);
                uVar10 = (undefined3)((uint)iVar5 >> 8);
                bVar9 = 1;
                bVar2 = *pbVar1;
                uStack_a0 = 1;
                if (bVar2 == *(byte *)(uVar14 + 1 + iVar6)) {
                  uVar7 = 1;
                  do {
                    if ((*(uint *)(*(int *)(iVar8 + iVar13) + 0xc) <= uVar7 + uVar14) ||
                       (0x3e < bVar9)) break;
                    bVar9 = bVar9 + 1;
                    uStack_a0 = (uint)bVar9;
                    uVar7 = (uint)bVar9;
                  } while (bVar2 == pbVar1[uVar7]);
                }
                if ((1 < bVar9) || (0xbf < bVar2)) {
                  stdFPutc(CONCAT31(uVar10,bVar9) | 0xc0,f);
                  uVar10 = extraout_var;
                }
                stdFPutc(CONCAT31(uVar10,*pbVar1),f);
                uVar14 = uVar14 + uStack_a0;
                iVar13 = *(int *)(bitmap + 0x78);
                iVar5 = *(int *)(iVar8 + iVar13);
              } while (uVar14 < *(uint *)(iVar5 + 0xc));
            }
            iVar13 = *(int *)(bitmap + 0x78);
            uStack_8c = uStack_8c + 1;
          } while (uStack_8c < *(uint *)(*(int *)(iVar13 + iVar8) + 0x10));
        }
      }
      else if (header.nType == 3) {
        stdDisplay_VBufferLock(*(VBuffer **)(iVar8 + *(int *)(bitmap + 0x78)));
        uStack_9c = *(undefined4 *)(*(int *)(iVar8 + *(int *)(bitmap + 0x78)) + 0x14);
        (*g_pStd_HS->pFwrite)(f,&uStack_9c,4);
        (*g_pStd_HS->pFwrite)
                  (f,*(undefined4 *)(*(int *)(iVar8 + *(int *)(bitmap + 0x78)) + 0x5c),uStack_9c);
        stdDisplay_VBufferUnlock(*(VBuffer **)(iVar8 + *(int *)(bitmap + 0x78)));
      }
      uStack_98 = uStack_98 + 1;
      iVar8 = iVar8 + 4;
    } while (uStack_98 < *(uint *)(bitmap + 100));
  }
  if (((*(byte *)(bitmap + 0x24) & 2) != 0) &&
     (iVar8 = (*g_pStd_HS->pFwrite)(f,*(undefined4 *)(bitmap + 0x60),0x300), iVar8 != 0x300)) {
    return 0;
  }
  return 1;
}

/* ---- 0x0047b250  stdBitmap_Write ---- */
/* Original name stdBitmap_Write (the remaster's GrimFandango (Linux): same body (open the file for
   writing, stdBitmap_AppendToFile, close); stdWriteImage's "bm" case in both builds); was
   stdBitmap_SaveBM. */

int __cdecl stdBitmap_Write(char *filename,void *bitmap)

{
  uint f;
  uint uVar1;
  
  f = (*g_pStd_HS->pFopen)(filename,s_wb__004ddb1c);
  if (f == 0) {
    return 0;
  }
  uVar1 = stdBitmap_AppendToFile(f,(int)bitmap);
  if (uVar1 == 0) {
    (*g_pStd_HS->pFclose)();
    return 0;
  }
  (*g_pStd_HS->pFclose)(f);
  return 1;
}

/* ---- 0x0047b2b0  stdBitmap_ConvertColorFormat ---- */
/* Deep copy of a 0x7c-byte bitmap record including its surfaces Original name
   stdBitmap_ConvertColorFormat (the remaster's GrimFandango (Linux): aligned call in
   sputRender_SaveDrawBuffer, sputRender_SaveScreen); was stdBitmap_CopyFrom. */

void __cdecl stdBitmap_ConvertColorFormat(ColorFormat *want,int have)

{
  VBuffer *pVVar1;
  int iVar2;
  ColorFormat *pCVar3;
  int *piVar4;
  int *srcFormat;
  bool bVar5;
  
  srcFormat = (int *)(have + 0x28);
  iVar2 = 0x38;
  bVar5 = true;
  pCVar3 = want;
  piVar4 = srcFormat;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = (char)pCVar3->nColorMode == (char)*piVar4;
    pCVar3 = (ColorFormat *)((int)&pCVar3->nColorMode + 1);
    piVar4 = (int *)((int)piVar4 + 1);
  } while (bVar5);
  if ((!bVar5) && ((*srcFormat != 0 || (want->nColorMode != 0)))) {
    iVar2 = 0;
    if (0 < *(int *)(have + 100)) {
      do {
        pVVar1 = *(VBuffer **)(*(int *)(have + 0x78) + iVar2 * 4);
        if (pVVar1->nType != 2) {
          pVVar1 = stdDisplay_VBufferConvertColorFormat(want,pVVar1);
          *(VBuffer **)(*(int *)(have + 0x78) + iVar2 * 4) = pVVar1;
          if (*(int *)(*(int *)(have + 0x78) + iVar2 * 4) == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_a_new_frame_w_004df5a8,
                       s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df55c + 0x15);
          }
          if ((*(byte *)(have + 0x24) & 1) != 0) {
            pVVar1 = *(VBuffer **)(*(int *)(have + 0x78) + iVar2 * 4);
            stdDisplay_VBufferSetColorKey(pVVar1,pVVar1->dwColorKey);
          }
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(have + 100));
    }
    if ((*(byte *)(have + 0x24) & 1) != 0) {
      iVar2 = stdColor_ColorConvertOnePixel((int)want,*(uint *)(have + 0x74),(int)srcFormat);
      *(int *)(have + 0x74) = iVar2;
    }
    for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
      *srcFormat = want->nColorMode;
      want = (ColorFormat *)&want->nBpp;
      srcFormat = srcFormat + 1;
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
stdBitmap_NewEntry(undefined4 *bitmap,uint width,uint height,uint frames,uint flags,
                  undefined4 *format)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = bitmap;
  for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  puVar1 = (undefined4 *)
           (*g_pStd_HS->pAlloc)
                     (width * 4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df570 + 0xb);
  bitmap[0x1e] = puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  for (uVar3 = width & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar1 = 0;
    puVar1 = (undefined4 *)((int)puVar1 + 1);
  }
  bitmap[9] = flags;
  bitmap[8] = frames;
  puVar1 = bitmap + 10;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *format;
    format = format + 1;
    puVar1 = puVar1 + 1;
  }
  bitmap[0x19] = width;
  bitmap[0x18] = height;
  return 1;
}

/* ---- 0x0047b540  stdBitmap_SetSurface ---- */
void __cdecl stdBitmap_SetSurface(int bitmap,int frame,uint surface)

{
  *(uint *)(*(int *)(bitmap + 0x78) + frame * 4) = surface;
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

void __cdecl stdBitmap_DeCompress(int bitmap)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < *(int *)(bitmap + 100)) {
    do {
      stdDisplay_VBufferDeCompress(*(VBuffer **)(*(int *)(bitmap + 0x78) + iVar1 * 4));
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(bitmap + 100));
  }
  *(undefined4 *)(bitmap + 0x20) = 0;
  return;
}

/* ---- 0x0047b5f0  stdPalEffects_ResetEffect ---- */
/* Zeroes 10 dwords and sets the gamma/scale field to 1.0 Original name stdPalEffects_ResetEffect
   (the remaster's GrimFandango (Linux): the call on rdroid_curColorEffects in rdOpen, same body
   (ten words cleared, +0x24 = 1.0f)); was stdBitmap_InitHeader. */

void __cdecl stdPalEffects_ResetEffect(undefined4 *effect)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = effect;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  effect[9] = 0x3f800000;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004df550[8] __asm__("_DAT_004df550");
extern unsigned char grim_def_DAT_004df558[4] __asm__("_DAT_004df558");
extern unsigned char grim_def_DAT_004df55c[12] __asm__("_DAT_004df55c");
extern unsigned char grim_def_DAT_004df568[8] __asm__("_DAT_004df568");
extern unsigned char grim_def_DAT_004df570[4] __asm__("_DAT_004df570");
extern char grim_def_s_BM_004df5a0[8] __asm__("_s_BM_004df5a0");
extern char grim_def_s_C__grimjedi_Libs_Std_General_Std_004df574[44] __asm__("_s_C__grimjedi_Libs_Std_General_Std_004df574");
extern char grim_def_s_Unable_to_allocate_a_new_frame_w_004df5a8[88] __asm__("_s_Unable_to_allocate_a_new_frame_w_004df5a8");
extern char grim_def_s__bm_004ddeb0[4] __asm__("_s__bm_004ddeb0");
extern char grim_def_s__bmp_004dde98[8] __asm__("_s__bmp_004dde98");
extern char grim_def_s__gif_004ddeb4[8] __asm__("_s__gif_004ddeb4");
extern char grim_def_s__lbm_004ddec4[8] __asm__("_s__lbm_004ddec4");
extern char grim_def_s__pcx_004ddebc[8] __asm__("_s__pcx_004ddebc");
extern char grim_def_s__pic_004ddea0[8] __asm__("_s__pic_004ddea0");
extern char grim_def_s__zbm_004ddea8[8] __asm__("_s__zbm_004ddea8");
extern char grim_def_s_bm_004ddee0[8] __asm__("_s_bm_004ddee0");
extern char grim_def_s_bmp_004ddecc[4] __asm__("_s_bmp_004ddecc");
extern char grim_def_s_gif_004dded0[4] __asm__("_s_gif_004dded0");
extern char grim_def_s_lbm_004dded8[4] __asm__("_s_lbm_004dded8");
extern char grim_def_s_pcx_004dded4[4] __asm__("_s_pcx_004dded4");
extern char grim_def_s_wb__004ddb1c[4] __asm__("_s_wb__004ddb1c");
extern char grim_def_s_zbm_004ddedc[4] __asm__("_s_zbm_004ddedc");
/* 0x004ddb1c, 4 bytes */ GRIM_DATA("004ddb1c") char grim_def_s_wb__004ddb1c[4] __asm__("_s_wb__004ddb1c") = "wb+";
/* 0x004dde98, 8 bytes */ GRIM_DATA("004dde98") char grim_def_s__bmp_004dde98[8] __asm__("_s__bmp_004dde98") = ".bmp";
/* 0x004ddea0, 8 bytes */ GRIM_DATA("004ddea0") char grim_def_s__pic_004ddea0[8] __asm__("_s__pic_004ddea0") = ".pic";
/* 0x004ddea8, 8 bytes */ GRIM_DATA("004ddea8") char grim_def_s__zbm_004ddea8[8] __asm__("_s__zbm_004ddea8") = ".zbm";
/* 0x004ddeb0, 4 bytes */ GRIM_DATA("004ddeb0") char grim_def_s__bm_004ddeb0[4] __asm__("_s__bm_004ddeb0") = ".bm";
/* 0x004ddeb4, 8 bytes */ GRIM_DATA("004ddeb4") char grim_def_s__gif_004ddeb4[8] __asm__("_s__gif_004ddeb4") = ".gif";
/* 0x004ddebc, 8 bytes */ GRIM_DATA("004ddebc") char grim_def_s__pcx_004ddebc[8] __asm__("_s__pcx_004ddebc") = ".pcx";
/* 0x004ddec4, 8 bytes */ GRIM_DATA("004ddec4") char grim_def_s__lbm_004ddec4[8] __asm__("_s__lbm_004ddec4") = ".lbm";
/* 0x004ddecc, 4 bytes */ GRIM_DATA("004ddecc") char grim_def_s_bmp_004ddecc[4] __asm__("_s_bmp_004ddecc") = "bmp";
/* 0x004dded0, 4 bytes */ GRIM_DATA("004dded0") char grim_def_s_gif_004dded0[4] __asm__("_s_gif_004dded0") = "gif";
/* 0x004dded4, 4 bytes */ GRIM_DATA("004dded4") char grim_def_s_pcx_004dded4[4] __asm__("_s_pcx_004dded4") = "pcx";
/* 0x004dded8, 4 bytes */ GRIM_DATA("004dded8") char grim_def_s_lbm_004dded8[4] __asm__("_s_lbm_004dded8") = "lbm";
/* 0x004ddedc, 4 bytes */ GRIM_DATA("004ddedc") char grim_def_s_zbm_004ddedc[4] __asm__("_s_zbm_004ddedc") = "zbm";
/* 0x004ddee0, 8 bytes */ GRIM_DATA("004ddee0") char grim_def_s_bm_004ddee0[8] __asm__("_s_bm_004ddee0") = "bm";
/* 0x004df550, 8 bytes */ GRIM_DATA("004df550") unsigned char grim_def_DAT_004df550[8] __asm__("_DAT_004df550") = { 0x3c, 0x00, 0x00, 0x00, 0x5f };
/* 0x004df558, 4 bytes */ GRIM_DATA("004df558") unsigned char grim_def_DAT_004df558[4] __asm__("_DAT_004df558") = { 0xaf };
/* 0x004df55c, 12 bytes */ GRIM_DATA("004df55c") unsigned char grim_def_DAT_004df55c[12] __asm__("_DAT_004df55c") = { 0x82, 0x02, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x6d, 0x03 };
/* 0x004df568, 8 bytes */ GRIM_DATA("004df568") unsigned char grim_def_DAT_004df568[8] __asm__("_DAT_004df568") = { 0x92, 0x03, 0x00, 0x00, 0xdc, 0x03 };
/* 0x004df570, 4 bytes */ GRIM_DATA("004df570") unsigned char grim_def_DAT_004df570[4] __asm__("_DAT_004df570") = { 0x0a, 0x04 };
/* 0x004df574, 44 bytes */ GRIM_DATA("004df574") char grim_def_s_C__grimjedi_Libs_Std_General_Std_004df574[44] __asm__("_s_C__grimjedi_Libs_Std_General_Std_004df574") = "C:\\grimjedi\\Libs\\Std\\General\\Stdbitmap.c";
/* 0x004df5a0, 8 bytes */ GRIM_DATA("004df5a0") char grim_def_s_BM_004df5a0[8] __asm__("_s_BM_004df5a0") = "BM  ";
/* 0x004df5a8, 88 bytes */ GRIM_DATA("004df5a8") char grim_def_s_Unable_to_allocate_a_new_frame_w_004df5a8[88] __asm__("_s_Unable_to_allocate_a_new_frame_w_004df5a8") = "Unable to allocate a new frame when converting image from 24 to 16bpp.\000\000%\000\000\000\263\001\000\000\321\001";
