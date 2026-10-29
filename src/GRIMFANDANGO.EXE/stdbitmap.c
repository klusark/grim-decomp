/* GRIMFANDANGO.EXE :: stdbitmap.c
 * functions 0x00473630 .. 0x0047b5f0 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00473630  stdBitmap_Load ---- */
/* Loads a .bm bitmap file; the frame surfaces hang off +0x78 */

void * __cdecl stdBitmap_Load(char *filename,int param_2,int param_3)

{
  void *pvVar1;
  
  pvVar1 = stdBitmap_LoadFile(filename,param_2,param_3);
  if (pvVar1 != (void *)0x0) {
    stdBitmap_DecompressAll(pvVar1);
  }
  return pvVar1;
}

/* ---- 0x00473660  stdBitmap_LoadFile ---- */
void * __cdecl stdBitmap_LoadFile(char *name,int a,int b)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined1 *puVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  #define local_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 *)(_frame + (0x20 - 0x4)))
  
  puVar2 = (undefined1 *)strrchr(name,0x2e);
  if (puVar2 == (undefined1 *)0x0) {
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
    puVar2 = &DAT_004ddec4;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  strncpy(local_8,puVar2,4);
  local_4 = 0;
  iVar5 = _stricmp(local_8,&DAT_004ddec4);
  if (iVar5 == 0) {
    pvVar3 = (void *)FUN_0047f120(name,a,b);
    return pvVar3;
  }
  iVar5 = _stricmp(local_8,&DAT_004ddebc);
  if (iVar5 == 0) {
    pvVar3 = (void *)stdLbm_Load(name,a,b);
    return pvVar3;
  }
  iVar5 = _stricmp(local_8,&DAT_004ddeb4);
  if (iVar5 == 0) {
    pvVar3 = (void *)stdPcx_Load(name,a,b);
    return pvVar3;
  }
  iVar5 = _stricmp(local_8,&DAT_004ddeb0);
  if ((iVar5 != 0) && (iVar5 = _stricmp(local_8,&DAT_004ddea8), iVar5 != 0)) {
    iVar5 = _stricmp(local_8,&DAT_004ddea0);
    if (iVar5 == 0) {
      pvVar3 = (void *)stdGif_Load(name,a,b);
      return pvVar3;
    }
    iVar5 = _stricmp(local_8,&DAT_004dde98);
    if (iVar5 != 0) {
      return (void *)0x0;
    }
    pvVar3 = (void *)stdBmp_Load(name,a,b);
    return pvVar3;
  }
  pvVar3 = stdBitmap_LoadResource(name,a,b);
  return pvVar3;
}
#undef local_4
#undef local_8


/* ---- 0x00473810  stdBitmap_SaveByExtension ---- */
/* Picks the writer from the file extension: .bm/.zbm (stdBitmap_SaveBM, zbm marks format 5), .bmp,
   .gif, .pcx, .lbm */

int __cdecl stdBitmap_SaveByExtension(char *filename,void *bitmap)

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
  
  pcVar2 = Str_FileExtension(filename);
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
    stdBitmap_DecompressAll(bitmap);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded8);
  if (iVar4 == 0) {
    iVar4 = stdLbm_Save(filename,bitmap);
    return (uint)(iVar4 != 0);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded4);
  if (iVar4 == 0) {
    iVar4 = stdPcx_Save(filename,bitmap);
    return (uint)(iVar4 != 0);
  }
  iVar4 = _stricmp(local_8,&DAT_004dded0);
  if (iVar4 != 0) {
    iVar4 = _stricmp(local_8,&DAT_004ddee0);
    if (iVar4 == 0) {
      iVar4 = stdBitmap_SaveBM(filename,bitmap);
      return (uint)(iVar4 != 0);
    }
    iVar4 = _stricmp(local_8,&DAT_004ddedc);
    if (iVar4 != 0) {
      iVar4 = _stricmp(local_8,&DAT_004ddecc);
      if (iVar4 != 0) {
        return 0;
      }
      iVar4 = stdBmp_Save(filename,bitmap);
      return (uint)(iVar4 != 0);
    }
    *(undefined4 *)((int)bitmap + 0x28) = 5;
    iVar4 = 0;
    if (0 < *(int *)((int)bitmap + 100)) {
      do {
        iVar4 = iVar4 + 1;
        *(undefined4 *)(*(int *)(*(int *)((int)bitmap + 0x78) + -4 + iVar4 * 4) + 0x20) = 5;
      } while (iVar4 < *(int *)((int)bitmap + 100));
    }
    iVar4 = stdBitmap_SaveBM(filename,bitmap);
    return (uint)(iVar4 != 0);
  }
  iVar4 = stdGif_Save(filename,bitmap);
  return (uint)(iVar4 != 0);
}
#undef local_4
#undef local_8


/* ---- 0x0047aa50  stdBitmap_LoadResource ---- */
/* Grim_ShowSplash loads splash.bm through this */

void * __cdecl stdBitmap_LoadResource(char *name,int a,int b)

{
  void *a_00;
  void *pvVar1;
  
  a_00 = (void *)(*g_pSvcMain->pAlloc)
                           (0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df550 + 4);
  if (a_00 != (void *)0x0) {
    pvVar1 = stdBitmap_LoadFromFile(name,(int)a_00,a,b);
    if (pvVar1 != (void *)0x0) {
      return a_00;
    }
    (*g_pSvcMain->pFree)(a_00);
  }
  return (void *)0x0;
}

/* ---- 0x0047aab0  stdBitmap_LoadFromFile ---- */
/* Stdbitmap.c: opens the file through the main services and reads a BM bitmap */

void * __cdecl stdBitmap_LoadFromFile(char *filename,int a,int b,int c)

{
  int iVar1;
  void *pvVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  iVar1 = (*g_pSvcMain->pFopen)(filename,&DAT_004ddb18);
  if (iVar1 == 0) {
    return (void *)0x0;
  }
  pvVar2 = (void *)stdBitmap_LoadBM(iVar1,a,b,c);
  uVar4 = 0x1f;
  pcVar3 = Str_FileNameFromPath(filename);
  strncpy(a,pcVar3,uVar4);
  *(undefined1 *)(a + 0x1f) = 0;
  (*g_pSvcMain->pFclose)(iVar1);
  return pvVar2;
}

/* ---- 0x0047ab20  stdBitmap_LoadBM ---- */
/* Reads the 'BM  ' header, palette/colour key and the per-mip surfaces (compressed or raw) */

undefined4 stdBitmap_LoadBM(undefined4 param_1,int param_2,int param_3,int param_4)

{
  unsigned char _frame[0xf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
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
  #define uStack_c4 (*(undefined4 *)(_frame + (0xf0 - 0xc4)))
  #define uStack_c0 (*(undefined4 *)(_frame + (0xf0 - 0xc0)))
  #define uStack_bc (*(undefined4 *)(_frame + (0xf0 - 0xbc)))
  #define uStack_b8 (*(undefined4 *)(_frame + (0xf0 - 0xb8)))
  #define uStack_b4 (*(undefined4 *)(_frame + (0xf0 - 0xb4)))
  #define uStack_b0 (*(undefined4 *)(_frame + (0xf0 - 0xb0)))
  #define auStack_ac (*(undefined1 (*)[96])(_frame + (0xf0 - 0xac)))
  #define auStack_4c (*(uint (*)[5])(_frame + (0xf0 - 0x4c)))
  #define auStack_38 (*(undefined4 (*)[14])(_frame + (0xf0 - 0x38)))
  
  (*g_pSvcMain->pFread)(param_1,local_cc,0x80);
  iVar4 = strncmp(local_cc,&DAT_004df5a0,4);
  if (iVar4 != 0) {
    return 0;
  }
  if (iStack_c8 == 0x46) {
    stdBitmap_Init(param_2,uStack_bc,0,uStack_c4,uStack_c0,auStack_ac);
    *(undefined4 *)(param_2 + 0x6c) = uStack_b8;
    *(undefined4 *)(param_2 + 0x74) = uStack_b0;
    puVar10 = auStack_4c;
    for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    uStack_e0 = 0;
    *(undefined4 *)(param_2 + 0x70) = uStack_b4;
    if (*(int *)(param_2 + 100) != 0) {
      do {
        (*g_pSvcMain->pFread)(param_1,&uStack_d4,8);
        auStack_4c[1] = uStack_d0;
        auStack_4c[0] = uStack_d4;
        puVar5 = (undefined4 *)(param_2 + 0x28);
        puVar11 = auStack_38;
        for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar11 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar11 = puVar11 + 1;
        }
        puVar5 = Surface_Create(auStack_4c,param_3,param_4,0);
        if (puVar5 == (undefined4 *)0x0) {
          return 0;
        }
        stdBitmap_SetSurface(param_2,uStack_e0,puVar5);
        Surface_Lock(puVar5);
        iVar4 = *(int *)(param_2 + 0x20);
        if (iVar4 == 0) {
          uVar6 = puVar5[9];
          iVar4 = puVar5[0x17];
          uVar9 = 0;
          iVar1 = puVar5[3];
          if (uStack_d0 != 0) {
            do {
              (*g_pSvcMain->pFread)(param_1,iVar4,(uVar6 >> 3) * iVar1);
              iVar4 = iVar4 + puVar5[6];
              uVar9 = uVar9 + 1;
            } while (uVar9 < uStack_d0);
          }
        }
        else if (iVar4 == 1) {
          pbVar8 = (byte *)puVar5[0x17];
          pbStack_d8 = pbVar8;
          if (puVar5[5] != 0) {
            do {
              bVar2 = stdFile_ReadByte(param_1);
              if ((bVar2 & 0xc0) == 0xc0) {
                uVar6 = bVar2 & 0x3f;
                bVar3 = stdFile_ReadByte(param_1);
                if ((bVar2 & 0x3f) != 0) {
                  pbVar12 = pbVar8;
                  for (uVar9 = uVar6 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                    *(uint *)pbVar12 = CONCAT22(CONCAT11(bVar3,bVar3),CONCAT11(bVar3,bVar3));
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar8 = pbStack_d8 + uVar6;
                  for (uVar6 = bVar2 & 3; pbStack_d8 = pbVar8, uVar6 != 0; uVar6 = uVar6 - 1) {
                    *pbVar12 = bVar3;
                    pbVar12 = pbVar12 + 1;
                  }
                }
              }
              else {
                *pbVar8 = bVar2;
                pbVar8 = pbVar8 + 1;
                pbStack_d8 = pbVar8;
              }
            } while ((uint)((int)pbVar8 - puVar5[0x17]) < (uint)puVar5[5]);
          }
        }
        else if ((iVar4 == 3) &&
                ((*g_pSvcMain->pFread)(param_1,&uStack_dc,4), uStack_dc < (uint)puVar5[5])) {
          uVar7 = (*g_pSvcMain->pAlloc)
                            (uStack_dc,s_C__grimjedi_Libs_Std_General_Std_004df574,
                             DAT_004df558 + 0x82);
          (*g_pSvcMain->pFread)(param_1,uVar7,uStack_dc);
          *puVar5 = 2;
          puVar5[5] = uStack_dc;
          (*g_pSvcMain->pFree)(puVar5[0x17]);
          puVar5[0x17] = uVar7;
        }
        Surface_Unlock(puVar5);
        if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
          Surface_SetColorKey(puVar5,*(int *)(param_2 + 0x74));
        }
        uStack_e0 = uStack_e0 + 1;
      } while (uStack_e0 < *(uint *)(param_2 + 100));
    }
    if ((*(byte *)(param_2 + 0x24) & 2) != 0) {
      iVar4 = (*g_pSvcMain->pAlloc)
                        (0x300,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df558 + 0x98);
      *(int *)(param_2 + 0x60) = iVar4;
      if (iVar4 == 0) {
        return 0;
      }
      (*g_pSvcMain->pFread)(param_1,iVar4,0x300);
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
  stdBitmap_FreeSurfaces(bitmap);
  (*g_pSvcMain->pFree)(bitmap);
  return;
}

/* ---- 0x0047ae90  stdBitmap_FreeSurfaces ---- */
/* Frees the surface array at +0x78 (+0x64 count) */

void stdBitmap_FreeSurfaces(int param_1)

{
  void *surface;
  uint uVar1;
  
  if (*(int *)(param_1 + 0x78) != 0) {
    uVar1 = 0;
    if (*(int *)(param_1 + 100) != 0) {
      do {
        surface = *(void **)(*(int *)(param_1 + 0x78) + uVar1 * 4);
        if (surface != (void *)0x0) {
          Surface_Free(surface);
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_1 + 100));
    }
    (*g_pSvcMain->pFree)(*(undefined4 *)(param_1 + 0x78));
  }
  if (*(int *)(param_1 + 0x60) != 0) {
    (*g_pSvcMain->pFree)(*(int *)(param_1 + 0x60));
  }
  return;
}

/* ---- 0x0047aef0  stdBitmap_WriteBM ---- */
/* Writes a BM bitmap (header, palette, surfaces) via stdFile */

undefined4 stdBitmap_WriteBM(undefined4 param_1,int param_2)

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
  iVar7 = (*g_pSvcMain->pFwrite)(param_1,&local_80,0x80);
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
      iVar4 = (*g_pSvcMain->pFwrite)(param_1,&iStack_94,8);
      if (iVar4 != 8) {
        return 0;
      }
      if (local_78 == 0) {
        Surface_Lock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_a4 = 0;
        iVar4 = *(int *)(iVar7 + *(int *)(param_2 + 0x78));
        iVar12 = *(int *)(iVar4 + 0x5c);
        iVar4 = (*(uint *)(iVar4 + 0x24) >> 3) * iStack_94;
        if (uStack_90 != 0) {
          do {
            iVar5 = (*g_pSvcMain->pFwrite)(param_1,iVar12,iVar4);
            if (iVar5 != iVar4) {
              return 0;
            }
            iVar12 = iVar12 + *(int *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x18);
            uStack_a4 = uStack_a4 + 1;
          } while (uStack_a4 < uStack_90);
        }
        Surface_Unlock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
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
                  stdFile_WriteByte(CONCAT31(uVar9,bVar8) | 0xc0,param_1);
                  uVar9 = extraout_var;
                }
                stdFile_WriteByte(CONCAT31(uVar9,*pbVar1),param_1);
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
        Surface_Lock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
        uStack_9c = *(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x14);
        (*g_pSvcMain->pFwrite)(param_1,&uStack_9c,4);
        (*g_pSvcMain->pFwrite)
                  (param_1,*(undefined4 *)(*(int *)(iVar7 + *(int *)(param_2 + 0x78)) + 0x5c),
                   uStack_9c);
        Surface_Unlock(*(void **)(iVar7 + *(int *)(param_2 + 0x78)));
      }
      uStack_98 = uStack_98 + 1;
      iVar7 = iVar7 + 4;
    } while (uStack_98 < *(uint *)(param_2 + 100));
  }
  if (((*(byte *)(param_2 + 0x24) & 2) != 0) &&
     (iVar7 = (*g_pSvcMain->pFwrite)(param_1,*(undefined4 *)(param_2 + 0x60),0x300), iVar7 != 0x300)
     ) {
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


/* ---- 0x0047b250  stdBitmap_SaveBM ---- */
int __cdecl stdBitmap_SaveBM(char *filename,void *bitmap)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (*g_pSvcMain->pFopen)(filename,&DAT_004ddb1c);
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = stdBitmap_WriteBM(iVar1,bitmap);
  if (iVar2 == 0) {
    (*g_pSvcMain->pFclose)();
    return 0;
  }
  (*g_pSvcMain->pFclose)(iVar1);
  return 1;
}

/* ---- 0x0047b2b0  stdBitmap_CopyFrom ---- */
/* Deep copy of a 0x7c-byte bitmap record including its surfaces */

void stdBitmap_CopyFrom(int *param_1,int param_2)

{
  void *surface;
  undefined4 uVar1;
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
          uVar1 = Surface_CreateFromBitmap(param_1,piVar3);
          *(undefined4 *)(*(int *)(param_2 + 0x78) + iVar2 * 4) = uVar1;
          if (*(int *)(*(int *)(param_2 + 0x78) + iVar2 * 4) == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Unable_to_allocate_a_new_frame_w_004df5a8,
                       s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df55c + 0x15);
          }
          if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
            surface = *(void **)(*(int *)(param_2 + 0x78) + iVar2 * 4);
            Surface_SetColorKey(surface,*(int *)((int)surface + 0x60));
          }
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(param_2 + 100));
    }
    if ((*(byte *)(param_2 + 0x24) & 1) != 0) {
      uVar1 = Pixel_ConvertOne(param_1,*(undefined4 *)(param_2 + 0x74),piVar5);
      *(undefined4 *)(param_2 + 0x74) = uVar1;
    }
    for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *param_1;
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    }
  }
  return;
}

/* ---- 0x0047b380  stdBitmap_Convert ---- */
/* Allocates a new bitmap and blits every surface into the requested pixel format */

int __cdecl stdBitmap_Convert(void *bitmap,int format,int flags)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar2 = (*g_pSvcMain->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 4);
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
  iVar3 = (*g_pSvcMain->pAlloc)(4,s_C__grimjedi_Libs_Std_General_Std_004df574,DAT_004df568 + 0x14);
  *(int *)(iVar2 + 0x78) = iVar3;
  if (iVar3 == 0) {
    return 0;
  }
  pvVar4 = Surface_Create((void *)((int)bitmap + 0xc),format,flags,0);
  **(undefined4 **)(iVar2 + 0x78) = pvVar4;
  if ((void *)**(undefined4 **)(iVar2 + 0x78) == (void *)0x0) {
    return 0;
  }
  Surface_Blit((void *)**(undefined4 **)(iVar2 + 0x78),bitmap,0,0,(int *)0x0,0);
  Surface_Unlock(bitmap);
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
             (*g_pSvcMain->pAlloc)
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

/* ---- 0x0047b4b0  stdBitmap_Init ---- */
/* Zeroes the 0x7c-byte record and stores the format/size/surface count */

undefined4
stdBitmap_Init(undefined4 *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 *param_6)

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
           (*g_pSvcMain->pAlloc)
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
void stdBitmap_SetSurface(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(*(int *)(param_1 + 0x78) + param_2 * 4) = param_3;
  return;
}

/* ---- 0x0047b560  stdBitmap_ConvertToDisplay ---- */
int __cdecl stdBitmap_ConvertToDisplay(void *bitmap)

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

/* ---- 0x0047b590  stdBitmap_DecompressAll ---- */
void stdBitmap_DecompressAll(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 100)) {
    do {
      Surface_Decompress(*(void **)(*(int *)(param_1 + 0x78) + iVar1 * 4));
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 100));
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}

/* ---- 0x0047b5f0  stdBitmap_InitHeader ---- */
/* Zeroes 10 dwords and sets the gamma/scale field to 1.0 */

void stdBitmap_InitHeader(undefined4 *param_1)

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
