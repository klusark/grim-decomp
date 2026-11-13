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

void * __cdecl stdLoadImage(char *filename,int param_2,int param_3)

{
  void *pvVar1;
  
  pvVar1 = stdLoadImageData(filename,param_2,param_3);
  if (pvVar1 != (void *)0x0) {
    stdBitmap_DeCompress((int)pvVar1);
  }
  return pvVar1;
}

/* ---- 0x00473660  stdLoadImageData ---- */
/* Original name stdLoadImageData (the remaster's GrimFandango (Linux): strings: '.bm' | '.pic' |
   '.zbm' | '.gif'); was stdBitmap_LoadFile. */

void * __cdecl stdLoadImageData(char *name,int a,int b)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined1 *puVar2;
  void *pvVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  #define local_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 *)(_frame + (0x20 - 0x4)))
  
  puVar2 = (undefined1 *)strrchr(name,0x2e);
  if (puVar2 == (undefined1 *)0x0) {
    uVar5 = 0xffffffff;
    pcVar8 = &DAT_004ddec4;
    do {
      pcVar10 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar6 = -1;
    pcVar8 = name;
    do {
      pcVar9 = pcVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    pcVar8 = pcVar10 + -uVar5;
    pcVar10 = pcVar9 + -1;
    for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    puVar2 = &DAT_004ddec4;
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
  }
  strncpy(local_8,puVar2,4);
  local_4 = 0;
  iVar6 = _stricmp(local_8,&DAT_004ddec4);
  if (iVar6 == 0) {
    pvVar3 = stdLbm_Load(name,a,b);
    return pvVar3;
  }
  iVar6 = _stricmp(local_8,&DAT_004ddebc);
  if (iVar6 == 0) {
    puVar4 = stdPcx_Load((uint)name,a,b);
    return puVar4;
  }
  iVar6 = _stricmp(local_8,&DAT_004ddeb4);
  if (iVar6 == 0) {
    pvVar3 = stdGif_Load(name,a,b);
    return pvVar3;
  }
  iVar6 = _stricmp(local_8,&DAT_004ddeb0);
  if ((iVar6 != 0) && (iVar6 = _stricmp(local_8,&DAT_004ddea8), iVar6 != 0)) {
    iVar6 = _stricmp(local_8,&DAT_004ddea0);
    if (iVar6 == 0) {
      pvVar3 = (void *)stdPic_Load((uint)name,a,b);
      return pvVar3;
    }
    iVar6 = _stricmp(local_8,&DAT_004dde98);
    if (iVar6 != 0) {
      return (void *)0x0;
    }
    pvVar3 = (void *)stdBmp_Load((uint)name,a,b);
    return pvVar3;
  }
  pvVar3 = stdBitmap_Load(name,a,b);
  return pvVar3;
}
#undef local_4
#undef local_8


/* ---- 0x00473810  stdWriteImage ---- */
/* Picks the writer from the file extension: .bm/.zbm (stdBitmap_Write, zbm marks format 5), .bmp,
   .gif, .pcx, .lbm Original name stdWriteImage (the remaster's GrimFandango (Linux): strings: 'lbm'
   | 'pcx' | 'zbm' | 'bmp'); was stdBitmap_SaveByExtension. */

int __cdecl stdWriteImage(char *filename,void *bitmap)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  #define local_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 *)(_frame + (0x20 - 0x4)))
  
  pcVar2 = stdFnames_FindExt(filename);
  if (pcVar2 == (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar2 = &DAT_004ddec4;
    do {
      pcVar6 = pcVar2;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar4 = -1;
    pcVar2 = filename;
    do {
      pcVar7 = pcVar2;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar7;
    } while (cVar1 != '\0');
    pcVar6 = pcVar6 + -uVar3;
    pcVar7 = pcVar7 + -1;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    pcVar2 = &DAT_004ddec4;
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  strncpy(local_8,pcVar2,4);
  local_4 = 0;
  iVar4 = _stricmp(local_8,&DAT_004ddee0);
  if ((iVar4 != 0) && (iVar4 = _stricmp(local_8,&DAT_004ddedc), iVar4 != 0)) {
    stdBitmap_DeCompress((int)bitmap);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded8);
  if (iVar4 == 0) {
    uVar3 = stdLbm_Write((uint)filename,(int)bitmap);
    return (uint)(uVar3 != 0);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded4);
  if (iVar4 == 0) {
    uVar3 = stdPcx_Write((uint)filename,(int)bitmap);
    return (uint)(uVar3 != 0);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded0);
  if (iVar4 != 0) {
    iVar4 = _stricmp(local_8,&DAT_004ddee0);
    if (iVar4 == 0) {
      iVar4 = stdBitmap_Write(filename,bitmap);
      return (uint)(iVar4 != 0);
    }
    iVar4 = _stricmp(local_8,&DAT_004ddedc);
    if (iVar4 != 0) {
      iVar4 = _stricmp(local_8,&DAT_004ddecc);
      if (iVar4 != 0) {
        return 0;
      }
      uVar3 = stdBmp_Write((uint)filename,(int)bitmap);
      return (uint)(uVar3 != 0);
    }
    *(undefined4 *)((int)bitmap + 0x28) = 5;
    iVar4 = 0;
    if (0 < *(int *)((int)bitmap + 100)) {
      do {
        iVar4 = iVar4 + 1;
        *(undefined4 *)(*(int *)(*(int *)((int)bitmap + 0x78) + -4 + iVar4 * 4) + 0x20) = 5;
      } while (iVar4 < *(int *)((int)bitmap + 100));
    }
    iVar4 = stdBitmap_Write(filename,bitmap);
    return (uint)(iVar4 != 0);
  }
  uVar3 = stdGif_Write((uint)filename,(int)bitmap);
  return (uint)(uVar3 != 0);
}
#undef local_4
#undef local_8


/* ---- 0x0047aa50  stdBitmap_Load ---- */
/* Grim_ShowSplash loads splash.bm through this Original name stdBitmap_Load (the remaster's
   GrimFandango (Linux): same body (allocate the 0x7c-byte bitmap in Stdbitmap.c, load it from the
   file, free it on failure)); was stdBitmap_LoadResource. */

void * __cdecl stdBitmap_Load(char *name,int a,int b)

{
  void *a_00;
  void *pvVar1;
  
  a_00 = (void *)(*g_pStd_HS->pAlloc)
                           (0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df550 + 4);
  if (a_00 != (void *)0x0) {
    pvVar1 = stdBitmap_LoadFromFile(name,(int)a_00,a,b);
    if (pvVar1 != (void *)0x0) {
      return a_00;
    }
    (*g_pStd_HS->pFree)(a_00);
  }
  return (void *)0x0;
}

/* ---- 0x0047aab0  stdBitmap_LoadFromFile ---- */
/* Stdbitmap.c: opens the file through the main services and reads a BM bitmap */

void * __cdecl stdBitmap_LoadFromFile(char *filename,int a,int b,int c)

{
  uint uVar1;
  void *pvVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  uVar1 = (*g_pStd_HS->pFopen)(filename,&DAT_004ddb18);
  if (uVar1 == 0) {
    return (void *)0x0;
  }
  pvVar2 = (void *)stdBitmap_LoadEntryFromFile(uVar1,a,b,c);
  uVar4 = 0x1f;
  pcVar3 = stdFileFromPath(filename);
  strncpy(a,pcVar3,uVar4);
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
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  byte *pbVar8;
  uint uVar9;
  uint *puVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  #define uStack_e0 (*(uint *)(_frame + (0xf0 - 0xe0)))
  #define uStack_dc (*(uint *)(_frame + (0xf0 - 0xdc)))
  #define pbStack_d8 (*(byte **)(_frame + (0xf0 - 0xd8)))
  #define uStack_d4 (*(uint *)(_frame + (0xf0 - 0xd4)))
  #define uStack_d0 (*(uint *)(_frame + (0xf0 - 0xd0)))
  #define local_cc (*(undefined1 (*)[4])(_frame + (0xf0 - 0xcc)))
  #define iStack_c8 (*(int *)(_frame + (0xf0 - 0xc8)))
  #define uStack_c4 (*(uint *)(_frame + (0xf0 - 0xc4)))
  #define uStack_c0 (*(uint *)(_frame + (0xf0 - 0xc0)))
  #define uStack_bc (*(uint *)(_frame + (0xf0 - 0xbc)))
  #define uStack_b8 (*(undefined4 *)(_frame + (0xf0 - 0xb8)))
  #define uStack_b4 (*(undefined4 *)(_frame + (0xf0 - 0xb4)))
  #define uStack_b0 (*(undefined4 *)(_frame + (0xf0 - 0xb0)))
  #define auStack_ac (*(uint (*)[24])(_frame + (0xf0 - 0xac)))
  #define auStack_4c (*(uint (*)[5])(_frame + (0xf0 - 0x4c)))
  #define auStack_38 (*(undefined4 (*)[14])(_frame + (0xf0 - 0x38)))
  
  (*g_pStd_HS->pFread)(param_1,local_cc,0x80);
  iVar3 = strncmp(local_cc,&DAT_004df5a0,4);
  if (iVar3 != 0) {
    return 0;
  }
  if (iStack_c8 == 0x46) {
    stdBitmap_NewEntry((uint *)param_2,uStack_bc,0,uStack_c4,uStack_c0,auStack_ac);
    *(undefined4 *)(param_2 + 0x6c) = uStack_b8;
    *(undefined4 *)(param_2 + 0x74) = uStack_b0;
    puVar10 = auStack_4c;
    for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    uStack_e0 = 0;
    *(undefined4 *)(param_2 + 0x70) = uStack_b4;
    if (*(int *)(param_2 + 100) != 0) {
      do {
        (*g_pStd_HS->pFread)(param_1,&uStack_d4,8);
        auStack_4c[1] = uStack_d0;
        auStack_4c[0] = uStack_d4;
        puVar4 = (undefined4 *)(param_2 + 0x28);
        puVar11 = auStack_38;
        for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar11 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar11 = puVar11 + 1;
        }
        puVar4 = stdDisplay_VBufferNew(auStack_4c,param_3,param_4,0);
        if (puVar4 == (undefined4 *)0x0) {
          return 0;
        }
        stdBitmap_SetSurface(param_2,uStack_e0,(uint)puVar4);
        stdDisplay_VBufferLock(puVar4);
        iVar3 = *(int *)(param_2 + 0x20);
        if (iVar3 == 0) {
          uVar5 = puVar4[9];
          iVar3 = puVar4[0x17];
          uVar9 = 0;
          iVar1 = puVar4[3];
          if (uStack_d0 != 0) {
            do {
              (*g_pStd_HS->pFread)(param_1,iVar3,(uVar5 >> 3) * iVar1);
              iVar3 = iVar3 + puVar4[6];
              uVar9 = uVar9 + 1;
            } while (uVar9 < uStack_d0);
          }
        }
        else if (iVar3 == 1) {
          pbVar8 = (byte *)puVar4[0x17];
          pbStack_d8 = pbVar8;
          if (puVar4[5] != 0) {
            do {
              uVar5 = stdFGetc(param_1);
              if (((byte)uVar5 & 0xc0) == 0xc0) {
                uVar9 = uVar5 & 0x3f;
                uVar6 = stdFGetc(param_1);
                bVar2 = (byte)uVar6;
                if (uVar9 != 0) {
                  pbVar12 = pbVar8;
                  for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(uint *)pbVar12 = CONCAT22(CONCAT11(bVar2,bVar2),CONCAT11(bVar2,bVar2));
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar8 = pbStack_d8 + uVar9;
                  for (uVar5 = uVar5 & 3; pbStack_d8 = pbVar8, uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pbVar12 = bVar2;
                    pbVar12 = pbVar12 + 1;
                  }
                }
              }
              else {
                *pbVar8 = (byte)uVar5;
                pbVar8 = pbVar8 + 1;
                pbStack_d8 = pbVar8;
              }
            } while ((uint)((int)pbVar8 - puVar4[0x17]) < (uint)puVar4[5]);
          }
        }
        else if ((iVar3 == 3) &&
                ((*g_pStd_HS->pFread)(param_1,&uStack_dc,4), uStack_dc < (uint)puVar4[5])) {
          uVar7 = (*g_pStd_HS->pAlloc)
                            (uStack_dc,s_C__grimjedi_Libs_Std_General_Std_004df574,
                             DAT_004df558 + 0x82);
          (*g_pStd_HS->pFread)(param_1,uVar7,uStack_dc);
          *puVar4 = 2;
          puVar4[5] = uStack_dc;
          (*g_pStd_HS->pFree)(puVar4[0x17]);
          puVar4[0x17] = uVar7;
        }
        stdDisplay_VBufferUnlock(puVar4);
        if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
          stdDisplay_VBufferSetColorKey(puVar4,*(int *)(param_2 + 0x74));
        }
        uStack_e0 = uStack_e0 + 1;
      } while (uStack_e0 < *(uint *)(param_2 + 100));
    }
    if ((*(byte *)(param_2 + 0x24) & 2) != 0) {
      iVar3 = (*g_pStd_HS->pAlloc)
                        (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df558 + 0x98);
      *(int *)(param_2 + 0x60) = iVar3;
      if (iVar3 == 0) {
        return 0;
      }
      (*g_pStd_HS->pFread)(param_1,iVar3,0x300);
    }
    return 1;
  }
  return 0;
}
#undef auStack_38
#undef auStack_4c
#undef auStack_ac
#undef iStack_c8
#undef local_cc
#undef pbStack_d8
#undef uStack_b0
#undef uStack_b4
#undef uStack_b8
#undef uStack_bc
#undef uStack_c0
#undef uStack_c4
#undef uStack_d0
#undef uStack_d4
#undef uStack_dc
#undef uStack_e0


/* ---- 0x0047ae70  stdBitmap_Free ---- */
void __cdecl stdBitmap_Free(void *bitmap)

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
  void *surface;
  uint uVar1;
  
  if (*(int *)(param_1 + 0x78) != 0) {
    uVar1 = 0;
    if (*(int *)(param_1 + 100) != 0) {
      do {
        surface = *(void **)(*(int *)(param_1 + 0x78) + uVar1 * 4);
        if (surface != (void *)0x0) {
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
  undefined4 *puVar11;
  int iVar12;
  uint uVar13;
  #define uStack_a4 (*(uint *)(_frame + (0xc0 - 0xa4)))
  #define uStack_a0 (*(uint *)(_frame + (0xc0 - 0xa0)))
  #define uStack_9c (*(undefined4 *)(_frame + (0xc0 - 0x9c)))
  #define uStack_98 (*(uint *)(_frame + (0xc0 - 0x98)))
  #define iStack_94 (*(int *)(_frame + (0xc0 - 0x94)))
  #define uStack_90 (*(uint *)(_frame + (0xc0 - 0x90)))
  #define uStack_8c (*(uint *)(_frame + (0xc0 - 0x8c)))
  #define iStack_88 (*(int *)(_frame + (0xc0 - 0x88)))
  #define uStack_84 (*(uint *)(_frame + (0xc0 - 0x84)))
  #define local_80 (*(undefined4 *)(_frame + (0xc0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xc0 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0xc0 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0xc0 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0xc0 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0xc0 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0xc0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xc0 - 0x64)))
  #define local_60 (*(undefined4 (*)[24])(_frame + (0xc0 - 0x60)))
  
  puVar10 = &local_80;
  for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  strncpy(&local_80,&DAT_004df5a0,4);
  local_7c = 0x46;
  local_78 = *(uint *)(param_2 + 0x20);
  local_74 = *(uint *)(param_2 + 0x24);
  local_70 = *(uint *)(param_2 + 100);
  local_6c = *(uint *)(param_2 + 0x6c);
  local_68 = *(uint *)(param_2 + 0x70);
  local_64 = *(uint *)(param_2 + 0x74);
  puVar10 = (undefined4 *)(param_2 + 0x28);
  puVar11 = local_60;
  for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar11 = puVar11 + 1;
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
        stdDisplay_VBufferLock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_a4 = 0;
        iVar4 = *(int *)(iVar7 + *(int *)(param_2 + 0x78));
        iVar12 = *(int *)(iVar4 + 0x5c);
        iVar4 = (*(uint *)(iVar4 + 0x24) >> 3) * iStack_94;
        if (uStack_90 != 0) {
          do {
            iVar5 = (*g_pStd_HS->pFwrite)(param_1,iVar12,iVar4);
            if (iVar5 != iVar4) {
              return 0;
            }
            iVar12 = iVar12 + *(int *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x18);
            uStack_a4 = uStack_a4 + 1;
          } while (uStack_a4 < uStack_90);
        }
        stdDisplay_VBufferUnlock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
      }
      else if (local_78 == 1) {
        iVar4 = *(int *)(param_2 + 0x78);
        uStack_8c = 0;
        iStack_88 = *(int *)(*(int *)(iVar7 + iVar4) + 0x5c);
        if (*(int *)(*(int *)(iVar7 + iVar4) + 0x10) != 0) {
          do {
            iVar12 = *(int *)(*(int *)(iVar7 + iVar4) + 0xc);
            iVar5 = uStack_8c * iVar12 + iStack_88;
            uVar13 = 0;
            if (iVar12 != 0) {
              do {
                pbVar1 = (byte *)(iVar5 + uVar13);
                uVar9 = (undefined3)((uint)iVar12 >> 8);
                bVar8 = 1;
                bVar2 = *pbVar1;
                uStack_a0 = 1;
                if (bVar2 == *(byte *)(uVar13 + 1 + iVar5)) {
                  uVar6 = 1;
                  uStack_84 = *(uint *)(*(int *)(iVar7 + iVar4) + 0xc);
                  do {
                    if ((uStack_84 <= uVar6 + uVar13) || (0x3e < bVar8)) break;
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
                uVar13 = uVar13 + uStack_a0;
                iVar4 = *(int *)(param_2 + 0x78);
                iVar12 = *(int *)(iVar7 + iVar4);
              } while (uVar13 < *(uint *)(iVar12 + 0xc));
            }
            iVar4 = *(int *)(param_2 + 0x78);
            uStack_8c = uStack_8c + 1;
          } while (uStack_8c < *(uint *)(*(int *)(iVar4 + iVar7) + 0x10));
        }
      }
      else if (local_78 == 3) {
        stdDisplay_VBufferLock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_9c = *(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x14);
        (*g_pStd_HS->pFwrite)(param_1,&uStack_9c,4);
        (*g_pStd_HS->pFwrite)
                  (param_1,*(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x5c),
                   uStack_9c);
        stdDisplay_VBufferUnlock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
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
  void *pvVar1;
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
        piVar3 = *(int **)(*(int *)(param_2 + 0x78) + iVar2 * 4);
        if (*piVar3 != 2) {
          pvVar1 = stdDisplay_VBufferConvertColorFormat(param_1,piVar3);
          *(void **)(*(int *)(param_2 + 0x78) + iVar2 * 4) = pvVar1;
          if (*(int *)(*(int *)(param_2 + 0x78) + iVar2 * 4) == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_a_new_frame_w_004df5a8,
                       s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df55c + 0x15);
          }
          if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
            pvVar1 = *(void **)(*(int *)(param_2 + 0x78) + iVar2 * 4);
            stdDisplay_VBufferSetColorKey(pvVar1,*(int *)((int)pvVar1 + 0x60));
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

int __cdecl stdBitmap_VBufferToBitmap(void *bitmap,int format,int flags)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar2 = (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 4);
  *(undefined4 *)(iVar2 + 0x20) = 0;
  if (*(int *)((int)bitmap + 0x58) == 0) {
    *(undefined4 *)(iVar2 + 0x24) = 0;
  }
  else {
    *(undefined4 *)(iVar2 + 0x24) = 2;
  }
  *(undefined4 *)(iVar2 + 100) = 1;
  *(undefined4 *)(iVar2 + 0x68) = 0;
  *(undefined4 *)(iVar2 + 0x6c) = 0;
  *(undefined4 *)(iVar2 + 0x70) = 0;
  iVar3 = (*g_pStd_HS->pAlloc)(4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 0x14);
  *(int *)(iVar2 + 0x78) = iVar3;
  if (iVar3 == 0) {
    return 0;
  }
  pvVar4 = stdDisplay_VBufferNew((void *)((int)bitmap + 0xc),format,flags,0);
  **(undefined4 **)(iVar2 + 0x78) = pvVar4;
  if ((void *)**(undefined4 **)(iVar2 + 0x78) == (void *)0x0) {
    return 0;
  }
  Surface_Blit((void *)**(undefined4 **)(iVar2 + 0x78),bitmap,0,0,(int *)0x0,0);
  stdDisplay_VBufferUnlock(bitmap);
  bVar1 = *(byte *)(iVar2 + 0x24);
  puVar5 = (undefined4 *)(**(int **)(iVar2 + 0x78) + 0x20);
  puVar6 = (undefined4 *)(iVar2 + 0x28);
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  if ((bVar1 & 2) != 0) {
    puVar5 = (undefined4 *)
             (*g_pStd_HS->pAlloc)
                       (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 0x29);
    *(undefined4 **)(iVar2 + 0x60) = puVar5;
    if (puVar5 == (undefined4 *)0x0) {
      return 0;
    }
    puVar6 = *(undefined4 **)((int)bitmap + 0x58);
    for (iVar3 = 0xc0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar5 = puVar5 + 1;
    }
    return iVar2;
  }
  *(undefined4 *)(iVar2 + 0x60) = 0;
  return iVar2;
}

/* ---- 0x0047b4b0  stdBitmap_NewEntry ---- */
/* Zeroes the 0x7c-byte record and stores the format/size/surface count Original name
   stdBitmap_NewEntry (the remaster's GrimFandango (Linux): same parameters (bitmap, frame count,
   ...) and body (clear the 0x7c-byte record, allocate the frame array in Stdbitmap.c)); was
   stdBitmap_Init. */

uint __cdecl
stdBitmap_NewEntry(uint *param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint *param_6)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar1 = (undefined4 *)
           (*g_pStd_HS->pAlloc)
                     (param_2 * 4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df570 + 0xb);
  param_1[0x1e] = (uint)puVar1;
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
  puVar4 = param_1 + 10;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *param_6;
    param_6 = param_6 + 1;
    puVar4 = puVar4 + 1;
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

int __cdecl stdBitmap_MemUsage(void *bitmap)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = *(int *)((int)bitmap + 100);
  if (0 < iVar3) {
    piVar1 = *(int **)((int)bitmap + 0x78);
    do {
      if (*(int *)(*piVar1 + 8) == 0) {
        iVar2 = iVar2 + *(int *)(*piVar1 + 0x14);
      }
      piVar1 = piVar1 + 1;
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
      stdDisplay_VBufferDeCompress(*(void **)(*(int *)(param_1 + 0x78) + iVar1 * 4));
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

void __cdecl stdPalEffects_ResetEffect(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[9] = 0x3f800000;
  return;
}
