/* GRIMFANDANGO.EXE :: stdgif.c
 * functions 0x0047db00 .. 0x0047ec40 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047db00  stdGif_Load ---- */
/* stdLoadImageData loader for '.gif' (LZW through stdGif_LzwInitDecoder/DecodeNext, allocation
   string Stdgif.c); was named stdPcx_Load. */

stdBitmap * __cdecl stdGif_Load(char *path,int videoMem,int b)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint f;
  stdBitmap *bitmap;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  uint *puVar5;
  VBuffer **ppVVar6;
  VBuffer *pVVar7;
  int iVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  char cStack_81;
  int iStack_80;
  int iStack_7c;
  int *piStack_78;
  int iStack_74;
  int iStack_70;
  uint uStack_6c;
  GifImageDesc desc;
  GifHeader header;
  #define VStack_4c (*(VBufferFormat *)(_frame + (0x60 - 0x4c)))
  
  f = (*g_pStd_HS->pFopen)(path,s_rb_004ddb18);
  if (f == 0) {
    return (stdBitmap *)0x0;
  }
  uStack_6c = f;
  bitmap = (stdBitmap *)
           (*g_pStd_HS->pAlloc)
                     (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x13);
  if (bitmap != (stdBitmap *)0x0) {
    bitmap->pPalette = (void *)0x0;
    bitmap->ppFrames = (VBuffer **)0x0;
    (*g_pStd_HS->pFread)(f,&header,3);
    iVar2 = toupper((int)header.aSignature[0]);
    if (((iVar2 == 0x47) && (iVar2 = toupper((int)header.aSignature[1]), iVar2 == 0x49)) &&
       (iVar2 = toupper((int)header.aSignature[2]), iVar2 == 0x46)) {
      (*g_pStd_HS->pFread)(f,header.aVersion,3);
      (*g_pStd_HS->pFread)(f,&header.wWidth,2);
      (*g_pStd_HS->pFread)(f,&header.wHeight,2);
      (*g_pStd_HS->pFread)(f,&header.bFlags,1);
      (*g_pStd_HS->pFread)(f,&header.bBackground,1);
      (*g_pStd_HS->pFread)(f,&header.bAspect,1);
      if ((header.bFlags & 0x80) != 0) {
        pvVar3 = (void *)(*g_pStd_HS->pAlloc)
                                   (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,
                                    DAT_004e787c + 0x3b);
        bitmap->pPalette = pvVar3;
        if (pvVar3 == (void *)0x0) goto LAB_0047e02f;
        (*g_pStd_HS->pFread)(f,pvVar3,(short)(1 << (header.bFlags & 7) + 1) * 3);
      }
      if (((header.aVersion[0] == '8') && (header.aVersion[1] == '9')) &&
         (iVar2 = toupper((int)header.aVersion[2]), iVar2 == 0x41)) {
        uVar4 = stdFGetc(f);
        cVar1 = (char)uVar4;
        while (cVar1 == '!') {
          uVar4 = stdFGetc(f);
          cVar1 = (char)uVar4;
          while (cVar1 != '\0') {
            uVar4 = stdFGetc(f);
            cVar1 = (char)uVar4;
          }
          uVar4 = stdFGetc(f);
          cVar1 = (char)uVar4;
        }
      }
      else {
        uVar4 = stdFGetc(f);
        cVar1 = (char)uVar4;
      }
      if (cVar1 == ',') {
        (*g_pStd_HS->pFread)(f,&desc.wLeft,2);
        (*g_pStd_HS->pFread)(f,&desc.wTop,2);
        (*g_pStd_HS->pFread)(f,&desc.wWidth,2);
        (*g_pStd_HS->pFread)(f,&desc.wHeight,2);
        (*g_pStd_HS->pFread)(f,&desc.bFlags,1);
        uVar4 = 0x1f;
        puVar5 = (uint *)stdFileFromPath(path);
        strncpy((uint *)bitmap,puVar5,uVar4);
        bitmap->aName[0x1f] = '\0';
        bitmap->nType = 0;
        bitmap->dwPalFlags = 2;
        bitmap->nFrames = 1;
        bitmap->nCurFrame = 0;
        (bitmap->colorFormat).nColorMode = 0;
        (bitmap->colorFormat).nBpp = 8;
        ppVVar6 = (VBuffer **)
                  (*g_pStd_HS->pAlloc)
                            (4,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x73);
        bitmap->ppFrames = ppVVar6;
        if (ppVVar6 != (VBuffer **)0x0) {
          VStack_4c.nWidth = (int)(short)desc.wWidth;
          VStack_4c.nHeight = (int)(short)desc.wHeight;
          VStack_4c.colorFormat.nColorMode = 0;
          VStack_4c.colorFormat.nBpp = 8;
          pVVar7 = stdDisplay_VBufferNew(&VStack_4c,videoMem,b,0);
          *bitmap->ppFrames = pVVar7;
          if (*bitmap->ppFrames != (VBuffer *)0x0) {
            if ((desc.bFlags & 0x80) != 0) {
              bVar9 = desc.bFlags & 7;
              if (bitmap->pPalette == (void *)0x0) {
                pvVar3 = (void *)(*g_pStd_HS->pAlloc)
                                           (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,
                                            DAT_004e787c + 0x8a);
                bitmap->pPalette = pvVar3;
                if (pvVar3 == (void *)0x0) goto LAB_0047e02f;
              }
              (*g_pStd_HS->pFread)(f,bitmap->pPalette,(short)(1 << bVar9 + 1) * 3);
            }
            iVar2 = (*g_pStd_HS->pAlloc)
                              (((*bitmap->ppFrames)->format).nWidth + (int)(short)desc.wLeft,
                               s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x95);
            iStack_7c = iVar2;
            if (iVar2 != 0) {
              (*g_pStd_HS->pFread)(f,&cStack_81,1);
              stdGif_LzwInitDecoder((short)cStack_81);
              iVar10 = 0;
              iStack_74 = (-(uint)((desc.bFlags & 2) != 0) & 7) + 1;
              iStack_80 = 0;
              stdDisplay_VBufferLock(*bitmap->ppFrames);
              iStack_70 = 0;
              pVVar7 = *bitmap->ppFrames;
              if (0 < (pVVar7->format).nHeight) {
                piStack_78 = (int *)&DAT_004e780c;
                do {
                  iVar2 = 0;
                  if (0 < (pVVar7->format).nWidth + (int)(short)desc.wLeft) {
                    do {
                      uVar4 = stdGif_LzwDecodeNext(f);
                      *(char *)(iVar2 + iStack_7c) = (char)uVar4;
                      if ((uVar4 & 0xff) == 0xffffffff) {
                        (*g_pStd_HS->pFree)(iStack_7c);
                        goto LAB_0047e02f;
                      }
                      iVar2 = iVar2 + 1;
                    } while (iVar2 < ((*bitmap->ppFrames)->format).nWidth + (int)(short)desc.wLeft);
                  }
                  pVVar7 = *bitmap->ppFrames;
                  if (iVar10 <= (pVVar7->format).nHeight) {
                    iVar2 = (pVVar7->format).nWidth;
                    iVar8 = 0;
                    if (0 < iVar2) {
                      do {
                        iVar11 = iStack_7c + iVar8;
                        iVar8 = iVar8 + 1;
                        *(undefined1 *)((int)pVVar7->pPixels + iVar8 + iVar10 * iVar2 + -1) =
                             *(undefined1 *)(iVar11 + (short)desc.wLeft);
                        pVVar7 = *bitmap->ppFrames;
                        iVar2 = (pVVar7->format).nWidth;
                        iVar10 = iStack_80;
                        f = uStack_6c;
                      } while (iVar8 < iVar2);
                    }
                  }
                  iVar10 = iVar10 + iStack_74;
                  pVVar7 = *bitmap->ppFrames;
                  iVar8 = (pVVar7->format).nHeight;
                  if (iVar8 <= iVar10) {
                    iVar10 = piStack_78[1];
                    iStack_74 = piStack_78[2];
                    piStack_78 = piStack_78 + 2;
                  }
                  iStack_70 = iStack_70 + 1;
                  iVar2 = iStack_7c;
                  iStack_80 = iVar10;
                } while (iStack_70 < iVar8);
              }
              stdDisplay_VBufferUnlock(*bitmap->ppFrames);
              (*g_pStd_HS->pFree)(iVar2);
              (*g_pStd_HS->pFread)(f,&cStack_81,1);
              (*g_pStd_HS->pFclose)(f);
              return bitmap;
            }
          }
        }
      }
    }
  }
LAB_0047e02f:
  (*g_pStd_HS->pFclose)(f);
  if (bitmap != (stdBitmap *)0x0) {
    stdBitmap_Free(bitmap);
  }
  return (stdBitmap *)0x0;
}
#undef VStack_4c


/* ---- 0x0047e060  stdGif_Write ---- */
/* Original name stdGif_Write (the remaster's GrimFandango (Linux): same body (open, "GIF" "89a",
   the screen descriptor from the first frame, the LZW image data); stdWriteImage's "gif" case in
   both builds); was stdGif_Save. */

uint __cdecl stdGif_Write(uint filename,int bitmap)

{
  uint file;
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  GifImageDesc desc;
  GifHeader header;
  
  iVar3 = bitmap;
  file = (*g_pStd_HS->pFopen)(filename,s_wb_004ddd78);
  if (file != 0) {
    strncpy((uint *)&header,(uint *)s_GIF_004e78b0,3);
    (*g_pStd_HS->pFwrite)(file,&header,3);
    strncpy((uint *)header.aVersion,(uint *)s_89a_004e78ac,3);
    (*g_pStd_HS->pFwrite)(file,header.aVersion,3);
    header.wWidth = *(ushort *)(**(int **)(bitmap + 0x78) + 0xc);
    header.wHeight = *(ushort *)(**(int **)(bitmap + 0x78) + 0x10);
    header.bFlags = 0xf7;
    header.bBackground = 0;
    header.bAspect = 0;
    (*g_pStd_HS->pFwrite)(file,&header.wWidth,2);
    (*g_pStd_HS->pFwrite)(file,&header.wHeight,2);
    (*g_pStd_HS->pFwrite)(file,&header.bFlags,1);
    (*g_pStd_HS->pFwrite)(file,&header.bBackground,1);
    (*g_pStd_HS->pFwrite)(file,&header.bAspect,1);
    (*g_pStd_HS->pFwrite)(file,*(undefined4 *)(bitmap + 0x60),0x300);
    desc.bSeparator = 0x2c;
    desc.wLeft = 0;
    desc.wTop = 0;
    desc.wWidth = *(ushort *)(**(int **)(bitmap + 0x78) + 0xc);
    desc.wHeight = *(ushort *)(**(int **)(bitmap + 0x78) + 0x10);
    desc.bFlags = 0;
    (*g_pStd_HS->pFwrite)(file,&desc,1);
    (*g_pStd_HS->pFwrite)(file,&desc.wLeft,2);
    (*g_pStd_HS->pFwrite)(file,&desc.wTop,2);
    (*g_pStd_HS->pFwrite)(file,&desc.wWidth,2);
    (*g_pStd_HS->pFwrite)(file,&desc.wHeight,2);
    (*g_pStd_HS->pFwrite)(file,&desc.bFlags,1);
    iVar5 = 1;
    uVar7 = 0;
    iVar1 = 1 << (desc.bFlags & 7) + 1;
    if (1 < iVar1) {
      do {
        iVar5 = iVar5 * 2;
        uVar7 = uVar7 + 1;
      } while (iVar5 < iVar1);
    }
    if (uVar7 == 1) {
      uVar7 = 2;
    }
    uVar7 = stdGif_LzwInitEncoder(file,uVar7);
    if (((short)uVar7 == 0) &&
       (puVar2 = (undefined4 *)
                 (*g_pStd_HS->pAlloc)
                           (*(undefined4 *)(**(int **)(bitmap + 0x78) + 0xc),
                            s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e7880 + 0x55),
       puVar2 != (undefined4 *)0x0)) {
      stdDisplay_VBufferLock((VBuffer *)**(undefined4 **)(bitmap + 0x78));
      iVar1 = **(int **)(bitmap + 0x78);
      bitmap = 0;
      if (0 < *(int *)(iVar1 + 0x10)) {
        do {
          uVar7 = *(uint *)(iVar1 + 0xc);
          puVar6 = (undefined4 *)(bitmap * uVar7 + *(int *)(iVar1 + 0x5c));
          puVar8 = puVar2;
          for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
            puVar6 = (undefined4 *)((int)puVar6 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
          iVar1 = 0;
          if (0 < *(int *)(**(int **)(iVar3 + 0x78) + 0xc)) {
            do {
              uVar7 = stdGif_LzwEncodePixel(file,*(byte *)((int)puVar2 + iVar1));
              if ((short)uVar7 != 0) {
                (*g_pStd_HS->pFree)(puVar2);
                (*g_pStd_HS->pFclose)(file);
                return 0;
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < *(int *)(**(int **)(iVar3 + 0x78) + 0xc));
          }
          bitmap = bitmap + 1;
          iVar1 = **(int **)(iVar3 + 0x78);
        } while (bitmap < *(int *)(iVar1 + 0x10));
      }
      stdDisplay_VBufferUnlock((VBuffer *)**(undefined4 **)(iVar3 + 0x78));
      stdGif_LzwFinishEncode(file);
      *(undefined1 *)puVar2 = 0;
      iVar3 = (*g_pStd_HS->pFwrite)(file,puVar2,1);
      if (iVar3 == 1) {
        *(undefined1 *)puVar2 = 0x3b;
        iVar3 = (*g_pStd_HS->pFwrite)(file,puVar2,1);
        if (iVar3 == 1) {
          (*g_pStd_HS->pFree)(puVar2);
          (*g_pStd_HS->pFclose)(file);
          return 1;
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(file);
  return 0;
}

/* ---- 0x0047e3c0  stdGif_LzwInitDecoder ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sets the clear/end codes and code size from the root code size */

uint __cdecl stdGif_LzwInitDecoder(short bits)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  _DAT_00811b2c = 1 << ((byte)bits & 0x1f);
  PIECE(UINT_0080cbe4,0,2) = bits + 1;
  UINT_00812ecc = 0;
  _DAT_00812ebc = _DAT_00811b2c + 1;
  _DAT_0080cbe8 = _DAT_00811b2c + 2;
  DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  puVar3 = (undefined4 *)PTR_UINT_004e7874;
  _DAT_00812ec4 = (short)UINT_0080cbe4;
  for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  uVar1 = 0xff;
  iVar2 = 0xff;
  do {
    PTR_UINT_004e7878[iVar2] = (char)uVar1;
    uVar1 = uVar1 - 1;
    iVar2 = iVar2 + -1;
  } while (-1 < (short)uVar1);
  DAT_0080cbec = DAT_0080cbe8;
  PTR_00812ec0 = (int *)&DAT_00811b30;
  DAT_00811b28 = DAT_008155f0;
  DAT_00812ed0 = 0;
  return uVar1 & 0xffff0000;
}

/* ---- 0x0047e470  stdGif_LzwDecodeNext ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Returns the next decoded pixel, walking the prefix/suffix tables */

uint __cdecl stdGif_LzwDecodeNext(uint f)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (PTR_00812ec0 != (int *)&DAT_00811b30) {
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + -1);
    return CONCAT22((short)((uint)PTR_00812ec0 >> 0x10),(ushort)*(byte *)PTR_00812ec0);
  }
  uVar2 = getcode(f);
  if (-1 < (short)uVar2) {
    if ((short)uVar2 == _DAT_00811b2c) {
      puVar5 = (undefined4 *)PTR_UINT_004e7874;
      for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      UINT_00812ecc = 1;
      _DAT_0080cbec = CONCAT22(DAT_0080cbec_2,(short)_DAT_0080cbe8 + -1);
      uVar2 = getcode(f);
      if ((short)uVar2 == -1) {
        return uVar2;
      }
    }
    sVar1 = (short)uVar2;
    if (sVar1 == _DAT_00812ebc) {
      return CONCAT22((short)(uVar2 >> 0x10),0xffff);
    }
    if (DAT_0080cbec <= sVar1) {
      *(undefined1 *)PTR_00812ec0 = DAT_00812ec8;
      PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
      uVar2 = _DAT_0080cbe0;
    }
    sVar3 = (short)uVar2;
    iVar4 = (int)sVar3;
    if (_DAT_00812ebc <= iVar4) {
      do {
        *(undefined *)PTR_00812ec0 = PTR_UINT_004e7878[iVar4];
        PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
        sVar3 = *(short *)(PTR_UINT_004e7874 + iVar4 * 2);
        iVar4 = (int)sVar3;
      } while (_DAT_00812ebc <= iVar4);
    }
    _DAT_00812ec8 = (ushort)(byte)PTR_UINT_004e7878[sVar3];
    *(undefined *)PTR_00812ec0 = PTR_UINT_004e7878[sVar3];
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
    if (DAT_0080cbec < DAT_004e7800) {
      iVar4 = (int)DAT_0080cbec;
      sVar3 = DAT_0080cbec + 1;
      *(undefined2 *)(PTR_UINT_004e7874 + iVar4 * 2) = DAT_0080cbe0;
      PTR_UINT_004e7878[iVar4] = DAT_00812ec8;
      _DAT_0080cbec = CONCAT22(DAT_0080cbec_2,sVar3);
    }
    _DAT_0080cbe0 = CONCAT22(DAT_0080cbe0_2,sVar1);
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + -1);
    return CONCAT22((short)((uint)PTR_00812ec0 >> 0x10),(ushort)*(byte *)PTR_00812ec0);
  }
  return CONCAT22((short)(uVar2 >> 0x10),0xffff);
}

/* ---- 0x0047e600  getcode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name getcode (the remaster's GrimFandango (Linux): same body (code width grows with
   maxcode up to 12 bits, the clear flag resets it, data sub-blocks read through the std file
   service); the LZW code reader of stdGif_Load in both builds); was stdGif_LzwReadCode. */

uint __cdecl getcode(uint f)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  sbyte sVar4;
  undefined4 extraout_EDX;
  byte bVar5;
  byte bVar6;
  undefined4 unaff_EDI;
  uint uVar7;
  
  if (DAT_008155f4 < DAT_0080cbec) {
    sVar2 = _DAT_00812ec4 + 1;
    _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,sVar2);
    if (sVar2 == 0xc) {
      DAT_008155f4 = DAT_004e7800;
    }
    else {
      DAT_00812ec4 = (byte)sVar2;
      DAT_008155f4 = (short)(1 << (DAT_00812ec4 & 0x1f)) + -1;
    }
  }
  if (0 < (int)UINT_00812ecc) {
    _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,(short)UINT_0080cbe4);
    UINT_00812ecc = 0;
    DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  }
  if (DAT_00812ed0 == 0) {
    uVar3 = stdGif_ReadByte(f);
    if ((short)uVar3 == 0xffff) goto LAB_0047e760;
    DAT_00815600 = (byte)uVar3;
  }
  sVar4 = (sbyte)(DAT_00812ed0 & 7);
  cVar1 = -sVar4;
  bVar5 = cVar1 + 8;
  uVar7 = CONCAT22((short)((uint)unaff_EDI >> 0x10),(ushort)(DAT_00815600 >> sVar4));
  sVar2 = ((DAT_00812ed0 & 7) - 8) + (short)_DAT_00812ec4;
  bVar6 = bVar5;
  if (7 < sVar2) {
    uVar3 = stdGif_ReadByte(f);
    if ((short)uVar3 == 0xffff) goto LAB_0047e760;
    DAT_00815600 = (byte)uVar3;
    bVar6 = cVar1 + 0x10;
    uVar7 = uVar7 | (CONCAT31((int3)((uint)extraout_EDX >> 8),DAT_00815600) & 0xffff00ff) <<
                    (bVar5 & 0x1f);
    sVar2 = sVar2 + -8;
  }
  if (0 < sVar2) {
    uVar3 = stdGif_ReadByte(f);
    if ((short)uVar3 == 0xffff) {
LAB_0047e760:
      return CONCAT22((short)(uVar3 >> 0x10),0xffff);
    }
    DAT_00815600 = (byte)uVar3;
    uVar7 = uVar7 | (CONCAT22(sVar2 >> 0xf,(ushort)(byte)(&DAT_004e7868)[sVar2]) & uVar3) <<
                    (bVar6 & 0x1f);
  }
  DAT_00812ed0 = (byte)((char)DAT_00812ed0 + DAT_00812ec4) & 7;
  bVar6 = DAT_00812ec4 & 0x1f;
  return (1 << bVar6) - 1U & uVar7;
}

/* ---- 0x0047e770  stdGif_ReadByte ---- */
/* Reads the next byte from the GIF sub-block stream */

uint __cdecl stdGif_ReadByte(uint f)

{
  int in_EAX;
  int iVar1;
  
  if (DAT_00811b28 == DAT_008155f0) {
    DAT_008155f0 = 0;
    iVar1 = (*g_pStd_HS->pFread)(f,&DAT_008155f0,1);
    if (iVar1 != 1) {
      return CONCAT22((short)((uint)iVar1 >> 0x10),0xffff);
    }
    in_EAX = (*g_pStd_HS->pFread)(f,&DAT_0080cbf8,(int)DAT_008155f0);
    if (in_EAX != DAT_008155f0) {
      return CONCAT22((short)((uint)in_EAX >> 0x10),0xffff);
    }
    DAT_00811b28 = 0;
  }
  iVar1 = (int)DAT_00811b28;
  DAT_00811b28 = DAT_00811b28 + 1;
  return CONCAT22((short)((uint)in_EAX >> 0x10),(ushort)(byte)(&DAT_0080cbf8)[iVar1]);
}

/* ---- 0x0047e7f0  stdGif_LzwInitEncoder ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

uint __cdecl stdGif_LzwInitEncoder(uint file,uint bits)

{
  undefined2 extraout_var;
  uint uVar1;
  int iVar2;
  uint *puVar3;
  
  _DAT_008155f8 = 0;
  DAT_00812ed0 = 0;
  UINT_00812ecc = 0;
  PIECE(UINT_0080cbe4,0,2) = (short)bits + 1;
  _DAT_00811b2c = 1 << ((byte)bits & 0x1f);
  _DAT_00812ebc = _DAT_00811b2c + 1;
  _DAT_0080cbe8 = _DAT_00811b2c + 2;
  DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  DAT_0080cbec = (undefined2)_DAT_0080cbe8;
  puVar3 = &UINT_0080ccf8;
  _DAT_00812ec4 = (short)UINT_0080cbe4;
  for (iVar2 = 0x138b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  DAT_0080cbf0 = 1;
  iVar2 = (*g_pStd_HS->pFwrite)(file,&bits,1);
  if (iVar2 != 1) {
    return CONCAT22((short)((uint)iVar2 >> 0x10),1);
  }
  putcode(file,DAT_00811b2c);
  uVar1 = CONCAT22(extraout_var,DAT_008155f8);
  return uVar1;
}
#endif


/* ---- 0x0047e8b0  putcode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name putcode (the remaster's GrimFandango (Linux): same body (packs the code into the
   output buffer at the bit offset with the lmask / rmask tables); the LZW code writer of
   stdGif_Write in both builds); was stdGif_LzwWriteCode. */

void __cdecl putcode(uint f,short code)

{
  undefined4 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  ushort uVar5;
  short sVar6;
  short sVar7;
  
  uVar5 = DAT_00812ed0 & 7;
  sVar2 = (short)DAT_00812ed0 >> 3;
  DAT_00812ed0 = DAT_00812ed0 + _DAT_00812ec4;
  (&DAT_0080cbf8)[(short)(sVar2 + 1)] =
       (char)code << (sbyte)uVar5 & (&DAT_004e7858)[(short)uVar5] |
       (&DAT_004e7868)[(short)uVar5] & (&DAT_0080cbf8)[(short)(sVar2 + 1)];
  sVar3 = sVar2 + 2;
  sVar7 = (uVar5 - 8) + (short)_DAT_00812ec4;
  sVar6 = code >> (8U - (sbyte)uVar5 & 0x1f);
  if (7 < sVar7) {
    iVar4 = (int)sVar3;
    sVar3 = sVar2 + 3;
    (&DAT_0080cbf8)[iVar4] = (char)sVar6;
    sVar6 = sVar6 >> 8;
    sVar7 = sVar7 + -8;
  }
  if (sVar3 == 0x100) {
    stdGif_WriteSubBlock(f,0xff);
    DAT_00812ed0 = DAT_00812ed0 + -0x7f8;
    sVar3 = 1;
  }
  if (0 < sVar7) {
    if (sVar3 == 0xff) {
      stdGif_WriteSubBlock(f,0xfe);
      DAT_00812ed0 = DAT_00812ed0 + -0x7f0;
      sVar3 = 1;
    }
    (&DAT_0080cbf8)[sVar3] = (char)sVar6;
  }
  if (DAT_00812ed0 == 0x7f0) {
    stdGif_WriteSubBlock(f,0xfe);
    DAT_00812ed0 = 0;
  }
  if ((DAT_008155f4 < DAT_0080cbec) || (0 < (int)UINT_00812ecc)) {
    if (UINT_00812ecc != 0) {
      _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,(short)UINT_0080cbe4);
      UINT_00812ecc = 0;
      DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
      return;
    }
    _DAT_00812ec4 = _DAT_00812ec4 + 1;
    uVar1 = _DAT_00812ec4;
    if (_DAT_00812ec4 == 0xc) {
      DAT_008155f4 = DAT_004e7800;
      return;
    }
    DAT_008155f4 = (short)(1 << (DAT_00812ec4 & 0x1f)) + -1;
    _DAT_00812ec4 = uVar1;
  }
  return;
}

/* ---- 0x0047ea30  stdGif_LzwEncodePixel ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

uint __cdecl stdGif_LzwEncodePixel(uint file,byte pixel)

{
  ushort uVar2;
  uint uVar1;
  undefined2 extraout_var;
  short sVar3;
  int iVar4;
  undefined4 unaff_EBX;
  uint uVar5;
  
  _DAT_008155f8 = 0;
  if (DAT_0080cbf0 != 0) {
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(ushort)pixel);
    sVar3 = 0;
    UINT_0081560c = 0x138b;
    do {
      UINT_0081560c = UINT_0081560c * 2;
      sVar3 = sVar3 + 1;
    } while ((int)UINT_0081560c < 0x10000);
    DAT_0080cbf0 = 0;
    _DAT_00815608 = CONCAT22(DAT_00815608_2,8 - sVar3);
    return (uint)DAT_00815608_2 << 0x10;
  }
  uVar1 = CONCAT31((int3)((uint)unaff_EBX >> 8),pixel) & 0xffff00ff;
  UINT_0081560c = (uint)pixel * 0x1000 + (_DAT_00811b24 & 0xffff);
  uVar5 = uVar1 << (DAT_00815608 & 0x1f) ^ _DAT_00811b24;
  sVar3 = (short)uVar5;
  uVar2 = (ushort)(UINT_0081560c >> 0x10);
  if ((&UINT_0080ccf8)[sVar3] != UINT_0081560c) {
    if (-1 < (int)(&UINT_0080ccf8)[sVar3]) {
      iVar4 = 0x138b - uVar5;
      if (sVar3 == 0) {
        iVar4 = 1;
      }
      do {
        uVar5 = uVar5 - iVar4;
        if ((short)uVar5 < 0) {
          uVar5 = uVar5 + 0x138b;
        }
        sVar3 = (short)uVar5;
        if ((&UINT_0080ccf8)[sVar3] == UINT_0081560c) {
          _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar3 * 2));
          return (uint)uVar2 << 0x10;
        }
      } while (0 < (int)(&UINT_0080ccf8)[sVar3]);
    }
    putcode(file,DAT_00811b24);
    uVar5 = UINT_0081560c;
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(short)uVar1);
    if (DAT_004e7800 <= DAT_0080cbec) {
      stdGif_LzwClearTable(file);
      uVar1 = CONCAT22(extraout_var,DAT_008155f8);
      return uVar1;
    }
    *(short *)((int)&UINT_00812ed8 + sVar3 * 2) = DAT_0080cbec;
    (&UINT_0080ccf8)[sVar3] = uVar5;
    uVar1 = CONCAT22(sVar3 >> 0xf,DAT_008155f8);
    DAT_0080cbec = DAT_0080cbec + 1;
    return uVar1;
  }
  _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar3 * 2));
  return (uint)uVar2 << 0x10;
}
#endif


/* ---- 0x0047eba0  stdGif_LzwClearTable ---- */
void __cdecl stdGif_LzwClearTable(uint f)

{
  int iVar1;
  uint *puVar2;
  
  UINT_00812ecc = 1;
  puVar2 = &UINT_0080ccf8;
  for (iVar1 = 0x138b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  DAT_0080cbec = DAT_0080cbe8;
  putcode(f,DAT_00811b2c);
  return;
}

/* ---- 0x0047ebe0  stdGif_LzwFinishEncode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stdGif_LzwFinishEncode(uint f)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  uint uVar1;
  undefined2 uVar2;
  
  _DAT_008155f8 = 0;
  putcode(f,DAT_00811b24);
  putcode(f,DAT_00812ebc);
  uVar2 = extraout_var;
  if (DAT_00812ed0 != 1) {
    stdGif_WriteSubBlock(f,(short)(DAT_00812ed0 + 7 >> 3));
    uVar2 = extraout_var_00;
  }
  uVar1 = CONCAT22(uVar2,DAT_008155f8);
  return uVar1;
}

/* ---- 0x0047ec40  stdGif_WriteSubBlock ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl stdGif_WriteSubBlock(uint f,short size)

{
  int iVar1;
  
  DAT_0080cbf8 = (undefined1)size;
  iVar1 = (*g_pStd_HS->pFwrite)(f,&DAT_0080cbf8,size + 1);
  if (iVar1 != size + 1) {
    _DAT_008155f8 = _DAT_008155f8 + 1;
  }
  return;
}
